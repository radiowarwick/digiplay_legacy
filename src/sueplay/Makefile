#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	sueplay

# Create a library and whether it should be a static library
OUT_LIB		=	no
OUT_STATIC	=	no

# Enable QT support?
QT_ENABLED 	=	no

# .cpp modules from which to create output
MODS		=	sueplay
QT_MODS		=	
SHARED_MODS	=	DataAccess Config Logger Security dps DbTrigger

# Global header files on which dependance exists
HDRS		=

# Compiler and linker options
LIBS		=	-lpqxx -lm -lpthread -ldpsaudio

include $(ROOT)/src/Makefile.in
