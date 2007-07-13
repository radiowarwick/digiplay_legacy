#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	dpsaudio
VERSION		=	1

# Create a library and whether it should be a static library
OUT_LIB		=	yes
OUT_STATIC	=	no

# Enable QT support?
QT_ENABLED 	=	no

# .cpp modules from which to create output
MODS		=	AudioPacket Thread Component Input InputRaw Output OutputRaw \
				OutputDsp Process  ProcessMixer ProcessFader Counter \
				CounterTrigger
SHARED_MODS	=	

# Global header files on which dependance exists
HDRS		=	Audio.h

# Compiler and linker options
LIBS		=	-lm -lpthread

POSTCOMPILE =  cd $(ROOT)/lib; ln -sf lib$(OUT_BASE).so.$(VERSION) \
					lib$(OUT_BASE).so

include $(ROOT)/src/Makefile.in
