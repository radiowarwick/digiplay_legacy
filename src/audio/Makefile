#===============================================================
# RaW Digital Playout Makefile
# Relative Path to Root of tree
ROOT		=	../..

# Base name for output (executable name, library basename) and version
OUT_BASE	=	dpsaudio

# Create a library and whether it should be a static library
OUT_LIB		=	yes
OUT_STATIC	=	no

# Enable QT support?
QT_ENABLED 	=	no

# .cpp modules from which to create output
MODS		=	AudioPacket Component ComponentAudio ComponentMonitor \
				Input InputRaw InputFlac \
				Output OutputRaw OutputDsp \
				Process  ProcessMixer ProcessFader ProcessLink \
				Counter CounterTrigger CircularCache
SHARED_MODS	=	Thread Security Logger

# Global header files on which dependance exists
HDRS		=	Audio.h

# Compiler and linker options
LIBS		=	-lm -lFLAC++ -lpthread -ldl

POSTCOMPILE =  ln -sf lib$(OUT_BASE).so.$(VERSION) lib$(OUT_BASE).so

# Default target includes modules..
all: modules
clean: modules_clean

include $(ROOT)/src/Makefile.in

# Ugly hacks to build modules...
MODULES		=	OutputSO_jack \
				   OutputSO_oss \
				   OutputSO_alsa

MLIBS_OutputSO_jack	=	-ljack
MLIBS_OutputSO_alsa	=	-lasound

define make_module
$(addsuffix .so,$(1)): $(addsuffix .o,$(1))
	$(LD) -o $(addsuffix .so,$(1)) -shared $(addsuffix .o,$(1)) \
		$(MLIBS_$(1))
endef

modules: $(addsuffix .so,$(MODULES))

modules_clean:
	@rm -f $(addsuffix .so,$(MODULES)) $(addsuffix .o,$(MODULES))

$(foreach MODULE,$(MODULES),$(eval $(call make_module,$(MODULE))))
