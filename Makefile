INSTALLDIR=/usr/local/bin
DBHOST=127.0.0.1
DBNAME=digiplay
DBUSER=digiplay_user
SUEFILE=./sustainer.md5

# Programs we need
CC=g++
MOC=@/usr/share/qt3/bin/moc
UIC=@/usr/share/qt3/bin/uic

# Compiler and linker flags
STDFLAGS= -Wall -O3
QTFLAGS=$(STDFLAGS) -pipe -W -D_REENTRANT  -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -DQT_SHARED
STD_INCLUDE=-I/usr/include/postgresql -I./components -I./apps
QT_INCLUDE=$(STD_INCLUDE) -I/usr/share/qt3/mkspecs/default -Icomponents -I/usr/include/qt3 -Iapps/studio -I.tmp/
LIBS_STD=-lpq /usr/lib/libpqxx.a -lreadline -lm -lpthread
LIBS_QT= $(LIBS_STD) -L/usr/share/qt3/lib -L/usr/X11R6/lib -lqt-mt -lXext -lX11

# Object files for each executable target
SUEPLAY_OBJ=			components/config.o \
						components/audiochannel.o \
						components/audiomixer.o \
						components/audioplayer.o \
						apps/sueplay.o
SUESCHED_OBJ=			components/config.o \
						components/sched_bin.o \
						components/schedule.o \
						components/scheduler.o \
						apps/suesched.o
STUDIO_PLAY_OBJ=		apps/studio_play/main.o \
						apps/studio_play/frmPlayout.o \
						.tmp/moc_frmPlayout.o \
						components/config.o \
						components/audioplayer.o \
						components/audiomixer.o \
						components/audiochannel.o \
						components/playerThread.o \
						components/audiowallthread.o \
						components/clockThread.o \
						components/triggerThread.o
STUDIO_SEARCH_OBJ=		apps/studio_search/main.o \
						components/libsearch.o \
						components/track.o \
						components/config.o \
						components/triggerThread.o \
						components/clockThread.o \
						apps/studio_search/frmSearch.o \
						.tmp/moc_frmSearch.o
ADMIN_OBJ=				apps/admin/main.o \
						apps/admin/frmAdmin.o \
						apps/admin/frmAdminEditNewInfo.o \
						apps/admin/frmAdminAddMusic.o \
						.tmp/moc_frmAdmin.o \
						.tmp/moc_frmAdminEditNewInfo.o \
						.tmp/moc_frmAdminAddMusic.o \
						components/systemmanager.o \
						components/archivemanager.o \
						components/config.o
						
# Compilation commands
COMPILE=		@echo Compiling $<; $(CC) $(STDFLAGS) -c $(STD_INCLUDE) -o $@ $<
QTCOMPILE=		@echo Compiling $<; $(CC) $(QTFLAGS) -c $(QT_INCLUDE) -o $@ $<

# Cleans all executables, object files and intermediate files
# Returns the tree to repository state
clean:
	@echo Cleaning source tree...
	@find . -name *.o -exec rm {} \;
	@rm -rf ./.tmp ./bin ./doc/code 

# Creates the temporary directory for intermediate files
init:
	@mkdir -p .tmp bin bin/images

# Copies necessary images for the interfaces to the images directory
studio_play_images:
	@cp apps/studio_play/images/* bin/images

studio_search_images:
	@cp apps/studio_search/images/* bin/images

# Executable targets
all: digiplay
digiplay: sue studio admin
sue: sueplay suesched
sueplay: init $(SUEPLAY_OBJ)
	@echo Linking $@; $(CC) $(CPPFLAGS) -o bin/$@ $(SUEPLAY_OBJ) $(LIBS_STD)
suesched: init $(SUESCHED_OBJ)
	@echo Linking $@; $(CC) $(CPPFLAGS) -o bin/$@ $(SUESCHED_OBJ) $(LIBS_STD)
studio: studio_play studio_search
studio_play: init $(STUDIO_PLAY_OBJ) studio_play_images
	@echo Linking $@; $(CC) $(QTFLAGS) -o bin/$@ $(STUDIO_PLAY_OBJ) $(LIBS_QT)
studio_search: init $(STUDIO_SEARCH_OBJ) studio_search_images
	@echo Linking $@; $(CC) $(QTFLAGS) -o bin/$@ $(STUDIO_SEARCH_OBJ) $(LIBS_QT)
admin: init $(ADMIN_OBJ)
	@echo Linking $@; $(CC) $(QTFLAGS) -o bin/$@ $(ADMIN_OBJ) $(LIBS_QT)
docs: init
	@echo Generating code documentation...
	@mkdir -p doc/code
	@doxygen doc/digiplay-doxygen > .tmp/doxygen_output.txt 2>&1
	@echo Documentation generated. Check .tmp/doxygen_output.txt for details.
install:
	@echo Installing compiled applications into $(INSTALLDIR)...
	@cp -R ./bin/* $(INSTALLDIR)
uninstall:
	@echo Uninstalling from $(INSTALLDIR)...
	@rm -f $(INSTALLDIR)/sueplay $(INSTALLDIR)/suesched
	@rm -f $(INSTALLDIR)/admin $(INSTALLDIR)/studio_*
suebackup:
	@echo Connecting to $(DBHOST) as user $(DBUSER) (specified in Makefile)
	@echo Specify SUEFILE variable on command line to specify backup file.
	@echo Backing up sustainer playlist...
	@psql -h $(DBHOST) -t -c "SELECT md5 FROM audio WHERE sustainer='t'" -U $(DBUSER) $(DBNAME) | cut -d ' ' -f 2 > $(SUEFILE)
	@echo Saved to $(SUEFILE)
suerestore:
	@echo Connecting to $(DBHOST) as user $(DBUSER) (specified in Makefile)
	@echo Specify SUEFILE variable on command line to specify backup file.
	@echo Restoring sustainer playlist from $(SUEFILE)...
	@psql -q -h $(DBHOST) -U $(DBUSER) -c "UPDATE audio SET sustainer='f'; `xargs -i -a $(SUEFILE) -n 1 echo UPDATE audio SET sustainer=\'t\' WHERE md5=\'{}\'\;` " $(DBNAME)
	@echo Sustainer playlist restored.
playin: init
	@echo Compiling audio playin application...
	@gcc apps/playin/main.c apps/playin/md5.c -o bin/playin -lncurses -lform
	@cp apps/cdparanoia bin

# Module targets
components/archivemanager.o:	components/archivemanager.cpp \
								components/archivemanager.h
	$(COMPILE)
components/audiochannel.o:		components/audiochannel.cpp \
								components/audiochannel.h
	$(COMPILE)								
components/audiomixer.o:		components/audiomixer.cpp \
								components/audiomixer.h
	$(COMPILE)
components/audioplayer.o:		components/audioplayer.cpp \
								components/audioplayer.h
	$(COMPILE)
components/audiowallthread.o:	components/audiowallthread.cpp \
								components/audiowallthread.h
	$(QTCOMPILE)
components/clockThread.o:		components/clockThread.cpp \
								components/clockThread.h
	$(QTCOMPILE)
components/config.o:			components/config.cpp \
								components/config.h
	$(COMPILE)
components/libsearch.o:			components/libsearch.cpp \
								components/libsearch.h
	$(COMPILE)
components/playerThread.o:		components/playerThread.cpp \
								components/playerThread.h
	$(QTCOMPILE)
components/sched_bin.o:			components/sched_bin.cpp \
								components/sched_bin.h
	$(COMPILE)
components/schedule.o:			components/schedule.cpp \
								components/schedule.h
	$(COMPILE)
components/scheduler.o:			components/scheduler.cpp \
								components/scheduler.h
	$(COMPILE)
components/studioTrigger.o:		components/studioTrigger.cpp \
								components/studioTrigger.h
	$(COMPILE)
components/systemmanager.o:		components/systemmanager.cpp \
								components/systemmanager.h
	$(COMPILE)
components/track.o:				components/track.cpp \
								components/track.h
	$(COMPILE)
components/trackinfo.o:			components/trackinfo.cpp \
								components/trackinfo.h
	$(COMPILE)
components/triggerThread.o:		components/triggerThread.cpp \
								components/triggerThread.h
	$(QTCOMPILE)
apps/sueplay.o:					apps/sueplay.cpp
	$(COMPILE)
apps/suesched.o:				apps/suesched.cpp
	$(COMPILE)
###### ADMIN APPLICATION
apps/admin/main.o:          apps/admin/main.cpp \
                            .tmp/frmAdmin.h \
                            .tmp/frmAdminEditNewInfo.h \
							.tmp/frmAdminAddMusic.h
	$(QTCOMPILE)

# frmAdmin
apps/admin/frmAdmin.o:       .tmp/frmAdmin.cpp \
                            apps/admin/frmAdmin.ui.h \
                            .tmp/frmAdmin.h
	$(QTCOMPILE)
.tmp/moc_frmAdmin.o:		.tmp/moc_frmAdmin.cpp \
                            .tmp/frmAdmin.h
	$(QTCOMPILE)
.tmp/frmAdmin.h:            apps/admin/frmAdmin.ui
	$(UIC) $< -o $@
.tmp/frmAdmin.cpp:          .tmp/frmAdmin.h \
                            apps/admin/frmAdmin.ui \
                            apps/admin/frmAdmin.ui.h
	$(UIC) apps/admin/frmAdmin.ui -i frmAdmin.h -o $@
.tmp/moc_frmAdmin.cpp:      .tmp/frmAdmin.h
	$(MOC) .tmp/frmAdmin.h -o $@

# frmAdminEditNewInfo
apps/admin/frmAdminEditNewInfo.o:    .tmp/frmAdminEditNewInfo.cpp \
                            apps/admin/frmAdminEditNewInfo.ui.h \
                            .tmp/frmAdminEditNewInfo.h
	$(QTCOMPILE)
.tmp/moc_frmAdminEditNewInfo.o:  .tmp/moc_frmAdminEditNewInfo.cpp \
                            .tmp/frmAdminEditNewInfo.h
	$(QTCOMPILE)
.tmp/frmAdminEditNewInfo.h:	apps/admin/frmAdminEditNewInfo.ui
	$(UIC) $< -o $@
.tmp/frmAdminEditNewInfo.cpp:	.tmp/frmAdminEditNewInfo.h \
                            apps/admin/frmAdminEditNewInfo.ui
	$(UIC) apps/admin/frmAdminEditNewInfo.ui -i frmAdminEditNewInfo.h -o $@
.tmp/moc_frmAdminEditNewInfo.cpp:	.tmp/frmAdminEditNewInfo.h
	$(MOC) .tmp/frmAdminEditNewInfo.h -o $@

# frmAdminAddMusic
apps/admin/frmAdminAddMusic.o:	.tmp/frmAdminAddMusic.cpp \
							apps/admin/frmAdminAddMusic.ui.h \
							.tmp/frmAdminAddMusic.h
	$(QTCOMPILE)
.tmp/moc_frmAdminAddMusic.o:	.tmp/moc_frmAdminAddMusic.cpp \
							.tmp/frmAdminAddMusic.h
	$(QTCOMPILE)
.tmp/frmAdminAddMusic.h:	apps/admin/frmAdminAddMusic.ui
	$(UIC) $< -o $@
.tmp/frmAdminAddMusic.cpp:	.tmp/frmAdminAddMusic.h \
							apps/admin/frmAdminAddMusic.ui
	$(UIC) apps/admin/frmAdminAddMusic.ui -i frmAdminAddMusic.h -o $@
.tmp/moc_frmAdminAddMusic.cpp:	.tmp/frmAdminAddMusic.h
	$(MOC) .tmp/frmAdminAddMusic.h -o $@
	
###### STUDIO PLAY APPLICATION
apps/studio_play/main.o:	apps/studio_play/main.cpp \
							.tmp/frmPlayout.h
	$(QTCOMPILE)

# frmPlayout
apps/studio_play/frmPlayout.o:	.tmp/frmPlayout.cpp \
							apps/studio_play/frmPlayout.ui.h \
							.tmp/frmPlayout.h
	$(QTCOMPILE)
.tmp/frmPlayout.cpp:		apps/studio_play/frmPlayout.ui \
							apps/studio_play/frmPlayout.ui.h \
							.tmp/frmPlayout.h
	$(UIC) apps/studio_play/frmPlayout.ui -i frmPlayout.h -o $@
.tmp/frmPlayout.h:			apps/studio_play/frmPlayout.ui
	$(UIC) $< -o $@

.tmp/moc_frmPlayout.o:		.tmp/moc_frmPlayout.cpp \
							.tmp/frmPlayout.h 
	$(QTCOMPILE)
.tmp/moc_frmPlayout.cpp:	.tmp/frmPlayout.h
	$(MOC) .tmp/frmPlayout.h -o $@

###### STUDIO SEARCH APPLICATION
apps/studio_search/main.o:    apps/studio_search/main.cpp \
                            .tmp/frmSearch.h
	$(QTCOMPILE)

# frmSearch
apps/studio_search/frmSearch.o:  .tmp/frmSearch.cpp \
                            apps/studio_search/frmSearch.ui.h \
                            .tmp/frmSearch.h
	$(QTCOMPILE)
.tmp/frmSearch.cpp:			apps/studio_search/frmSearch.ui \
                            apps/studio_search/frmSearch.ui.h \
                            .tmp/frmSearch.h
	$(UIC) apps/studio_search/frmSearch.ui -i frmSearch.h -o $@
.tmp/frmSearch.h:          apps/studio_search/frmSearch.ui
	$(UIC) $< -o $@

.tmp/moc_frmSearch.o:      .tmp/moc_frmSearch.cpp \
                            .tmp/frmSearch.h 
	$(QTCOMPILE)
.tmp/moc_frmSearch.cpp:    .tmp/frmSearch.h
	$(MOC) .tmp/frmSearch.h -o $@

