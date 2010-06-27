#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	audioplay

# Create a library and whether it should be a static library
OUT_LIB		=	no
OUT_STATIC	=	no

# Enable QT support?
QT_ENABLED 	=	no

# .cpp modules from which to create output
MODS		=	audioplay
QT_MODS		=	
SHARED_MODS	=	

# Global header files on which dependance exists
HDRS		=

# Compiler and linker options
LIBS		=	-lpq -lpqxx -lreadline -lm -lpthread -ldpsaudio

include $(ROOT)/src/Makefile.in
