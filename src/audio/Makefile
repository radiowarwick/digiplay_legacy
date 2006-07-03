#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	audio
VERSION		=	1

# Create a library and whether it should be a static library
OUT_LIB		=	yes
OUT_STATIC	=	no

# Enable QT support?
QT_ENABLED 	=	no

# .cpp modules from which to create output
MODS		=	Thread Component Input InputRaw Output OutputRaw OutputDsp Process  ProcessMixer Counter
SHARED_MODS	=	

# Global header files on which dependance exists
HDRS		=	Audio.h

# Compiler and linker options
LIBS		=	-lm -lpthread

include $(ROOT)/src/Makefile.in
