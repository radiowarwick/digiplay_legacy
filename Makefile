STUDIO		=	audio studio_play studio_manage
SUE			=	audio sueplay suesched
ADMIN		=	admin tools playin
APPS		= 	$(STUDIO) $(SUE) $(ADMIN)

INSTALLDIR	=	/usr/local/bin
LIBDIR		=	/usr/local/lib
LOGDIR		=	/var/log/dps

studio: 	$(STUDIO)
sue:		$(SUE)
backend:	$(ADMIN)

all: $(APPS)

%:
	@if [ -d src/$@ ]; then \
		$(MAKE) -C src/$@; \
	else \
		OUTPUT=`find . -name "Makefile.$@" -type f`; \
		if [ ! "$${OUTPUT:-FAILED}" == "FAILED" ]; then \
			find . -name "Makefile.$@" -type f -execdir make -f {} \; ; \
		fi; \
	fi;

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
	@echo "Setting up logging directory $(LOGDIR)"
	@mkdir -p $(LOGDIR)
	@chmod 666 $(LOGDIR)
	@echo "Installation complete."


