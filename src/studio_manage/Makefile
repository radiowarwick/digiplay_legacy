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
QT_MODS		=	frmStudioManage TabPanel TabPanelInfo TabPanelEmail\
				TabPanelSearch TabPanelPlaylist TabPanelLogging\
				TabPanelScript
SHARED_MODS	=	config libsearch track dps clockThread triggerThread\
				Auth AuthLdap Logger

# Global header files on which dependance exists
HDRS		=

# Compiler and linker options
LIBS		=	-lpq /usr/lib/libpqxx.a -lreadline -lm -lpthread -lldap

POSTCOMPILE	=	if [ ! -e $(ROOT)/bin/images ]; \
					then mkdir $(ROOT)/bin/images; fi; \
					cp -R images/* $(ROOT)/bin/images

include $(ROOT)/src/Makefile.in
