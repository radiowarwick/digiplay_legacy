# Makefile for Digiplay

# Base for generated tarball
VERSION		= 	$(shell cat VERSION)
BASE		=	digiplay-$(VERSION)

# Installation locations
ifndef DESTDIR
BINDIR=/usr/local/bin
ETCDIR=/etc
LIBDIR=/usr/local/lib
MANDIR=/usr/local/share/man/man1
SHAREDIR=/usr/local/share/dps
DOCDIR=/usr/local/share/doc/dps
IMGDIR=$(SHAREDDIR)/images
else
BINDIR=$(DESTDIR)/usr/bin
ETCDIR=$(DESTDIR)/etc
LIBDIR=$(DESTDIR)/usr/lib
MANDIR=$(DESTDIR)/usr/share/man/man1
SHAREDDIR=$(DESTDIR)/usr/share
DOCDIR=$(SHAREDDIR)/doc/dps
IMGDIR=$(SHAREDDIR)/dps/images
endif

# Application groups
AUDIO		=	audio
STUDIO		=	studio_play studio_manage
SUE			=	sueplay suesched
ADMIN		=	dpsadmin
DATABASE	=	db
ALL			=	$(AUDIO) $(STUDIO) $(SUE) $(ADMIN) $(DATABASE)

# Built Executables
EXE_STUDIO_MANAGE	=	src/studio_manage/studio_manage
EXE_STUDIO_PLAY		=	src/studio_play/studio_play
EXE_DPSADMIN		=	src/dpsadmin/dpsadmin
EXE_SUEPLAY			=	src/sueplay/sueplay
EXE_SUESCHED		=	src/suesched/suesched
LIB_DPSAUDIO		=	src/audio/libdpsaudio.so \
						src/audio/libdpsaudio.so.$(VERSION)
EXE_ALL				=	$(EXE_STUDIO_MANAGE) $(EXE_STUDIO_PLAY) $(EXE_DPSADMIN)\
						$(EXE_SUEPLAY) $(EXE_SUESCHED)
LIB_ALL				=	$(LIB_DPSAUDIO)

.PHONY: clean install doc manual doxygen tar

### Build rules ###

studio: 	$(AUDIO) $(STUDIO)
sue:		$(AUDIO) $(SUE)
backend:	$(ADMIN)

all: 		$(ALL)

%:
	@if [ -d src/$@ ]; then \
		$(MAKE) -C src/$@; \
	else \
		OUTPUT=`find . -name "Makefile.$@" -type f`; \
		if [ ! "$${OUTPUT:-FAILED}" == "FAILED" ]; then \
			find . -name "Makefile.$@" -type f -execdir make -f {} \; ; \
		fi; \
	fi;

clean:
	@echo "Cleaning source tree"; \
	rm -rf bin lib src/*.o *.tar.gz
	@make -C doc/manual clean
	@-$(foreach APP,$(ALL), if [ -d src/$(APP) ]; then $(MAKE) -C src/$(APP) clean; fi;)

install:
	@mkdir -p $(BINDIR) $(ETCDIR) $(LIBDIR) $(MANDIR) $(SHAREDDIR) $(DOCDIR) \
				$(IMGDIR);
	@-$(foreach EXE,$(EXE_ALL), if [ -f $(EXE) ]; then cp -aP $(EXE) $(BINDIR); fi;)
	@-$(foreach LIB,$(LIB_ALL), if [ -f $(LIB) ]; then cp -aP $(LIB) $(LIBDIR); fi;)
	@cp -aP share/doc/examples/digiplay.conf $(ETCDIR)
	@-$(foreach EXE,$(EXE_ALL), if [ -f $(EXE) ]; then cp -aP share/man/man1/`echo $(EXE) | sed 's/.*\///'`.1 $(MANDIR); fi;)
	@cp -arP share/dps $(SHAREDDIR)
	@cp -arP share/doc/* $(SHAREDDIR)/doc/dps
	@echo "Installation complete."

doc: 		manual
manual:
	make -C doc/manual

doxygen:
	doxygen doc/doxygen.conf

tar: 		clean
	@echo "Generating tarball..."; \
	if [ -h $(BASE) ]; then rm $(BASE); fi; \
	ln -s . $(BASE); \
	tar -h --exclude $(BASE)/$(BASE) --exclude-from tar-exclude -cvf $(BASE).tar $(BASE) > /dev/null; \
	rm $(BASE); \
	gzip $(BASE).tar; \
	echo "Created $(BASE).tar.gz";

deb:
	@dpkg-buildpackage -us -uc -rfakeroot

deb-clean:
	@fakeroot -- make -f debian/rules clean
