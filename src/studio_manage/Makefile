#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	studio_manage
VERSION		=	1

# Create a library and whether it should be a static library
OUT_LIB		=	no
OUT_STATIC	=	no

# Enable QT support?
QT_ENABLED 	=	yes

# .cpp modules from which to create output
MODS		=	main
#QT_OBJS		=	dlgLogin dlgWarn
QT_MODS		=	frmStudioManage dlgLogin dlgWarn\
				TabPanel TabPanelInfo TabPanelEmail\
				TabPanelSearch TabPanelPlaylist TabPanelLogging\
				TabPanelScript TabPanelFileBrowser\
				FileBrowser Showplan ShowPlanItem Nownext
SHARED_MODS	=	Config DpsEmail dps clockThread \
				Auth AuthLdap AuthPsql Logger UserConfig \
				DataAccess Security Thread DbTrigger MessagingInterface \
				DpsMusicSearch
DPS_MODS	=	DpsObject DpsHash DpsTime DpsDate DpsUser DpsGroup DpsAudioItem DpsScriptItem DpsShowItem DpsShowPlan
SHARED_QT_MODS = QtTrigger

# Global header files on which dependance exists
HDRS		=

# Compiler and linker options
LIBS		=	-lpqxx -lm -lpthread

#POSTCOMPILE	=	if [ ! -e $(ROOT)/bin/images ]; \
#					then mkdir $(ROOT)/bin/images; fi; \
#					cp -R images/* $(ROOT)/bin/images

include $(ROOT)/src/Makefile.in
