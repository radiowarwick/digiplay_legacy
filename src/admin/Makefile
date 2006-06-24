#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	admin
VERSION		=	1

# Create a library and whether it should be a static library
OUT_LIB		=	no
OUT_STATIC	=	no

# .cpp modules from which to create output
MODS		=	

# Global header files on which dependance exists
HDRS		=

# Compiler and linker options
INC			=	-I/usr/include/postgresql
LIBS		=	-lpq /usr/lib/libpqxx.a -lreadline -lm -lpthread

include $(ROOT)/src/Makefile.in
