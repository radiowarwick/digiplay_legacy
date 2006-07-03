APPS		=	audio admin studio_play studio_manage sueplay suesched playin
INSTALLDIR	=	/usr/local/bin
LIBDIR		=	/usr/local/lib

all: $(APPS) 

%:
	@if [ -d src/$@ ]; then $(MAKE) -C src/$@; fi;

clean:
	@echo "Cleaning source tree"
	@rm -rf bin lib src/*.o
	@-$(foreach APP,$(APPS), if [ -d src/$(APP) ]; then $(MAKE) -C src/$(APP) clean; fi;)

install:
	@echo "Installing compiled applications in $(INSTALLDIR)"
	@cp bin/* $(INSTALLDIR)
	@echo "Installing libraries in $(LIBDIR)"
	@echo "Note: You may need to add $(LIBDIR) to your library search path"
	@cp lib/* $(LIBDIR)
