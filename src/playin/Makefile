#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	playin
VERSION		=	1

# Create a library and whether it should be a static library
OUT_LIB		=	no
OUT_STATIC	=	no

# Enable QT support?
QT_ENABLED 	=	no

# .cpp modules from which to create output
MODS		=	main md5
QT_MODS		=
SHARED_MODS	=	Config dps DbTrigger Thread DataAccess Logger Security \
				SystemManager ArchiveManager XmlDocument XmlElement

# Global header files on which dependance exists
HDRS		=

# Compiler and linker options
LIBS		=	-lncurses -lform -lpqxx -lpthread

# Compiled binaries are no longer put in $(ROOT)/bin
#POSTCOMPILE =   cp cdparanoia $(ROOT)/bin

# Include make rules and change any default variables
include $(ROOT)/src/Makefile.in
CCFLAGS         =      -D'VERSION="$(VERSION)"'
#CC			=	gcc $(CCFLAGS)
md5.o:	md5.c
	gcc -c md5.c -o md5.o


