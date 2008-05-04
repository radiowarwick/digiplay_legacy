#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	studio_play

# Create a library and whether it should be a static library
OUT_LIB		=	no
OUT_STATIC	=	no

# Enable QT support?
QT_ENABLED 	=	yes

# .cpp modules from which to create output
MODS		=	main
QT_MODS		=	frmPlayout AudioWall AudioWallItem AudioWallManager \
				AudioPlayer AudioWallDriver RemoteStartThread
SHARED_MODS	=	Config Logger dps DataAccess Security clockThread Thread \
				DbTrigger MessagingInterface
SHARED_QT_MODS	= QtTrigger

# Global header files on which dependance exists
HDRS		=

# Compiler and linker options
LIBS		=	-lpq /usr/lib/libpqxx.a -lm -lpthread -ldpsaudio

#POSTCOMPILE	=	if [ ! -e $(ROOT)/bin/images ]; \
#					then mkdir $(ROOT)/bin/images; fi; \
#					cp -R images/* $(ROOT)/bin/images

include $(ROOT)/src/Makefile.in
