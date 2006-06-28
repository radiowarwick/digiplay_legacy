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

# modules from which to create output
MODS		=	Thread Component Input InputRaw Output OutputRaw OutputPlayer Process ProcessMixer Counter

# Global header files on which dependance exists
HDRS		=	Audio.h

# Compiler and linker options
INC			=	
LIBS		=	-lm -lpthread

include $(ROOT)/src/Makefile.in
