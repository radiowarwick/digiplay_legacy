STUDIO		=	audio studio_play studio_manage
SUE			=	audio sueplay suesched
ADMIN		=	admin admintools playin
APPS		= 	$(STUDIO) $(SUE) $(ADMIN)

INSTALLDIR	=	/usr/local/bin
LIBDIR		=	/usr/local/lib

studio: 	$(STUDIO)
sue:		$(SUE)
admin:		$(ADMIN)

all: studio sue admin

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
