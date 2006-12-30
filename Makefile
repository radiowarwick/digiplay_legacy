STUDIO		=	audio studio_play studio_manage
SUE			=	audio sueplay suesched
ADMIN		=	tools
APPS		= 	$(STUDIO) $(SUE) $(ADMIN)

studio: 	$(STUDIO)
sue:		$(SUE)
backend:	$(ADMIN)

.PHONY: clean install

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
	@rm -rf bin lib src/*.o *.tar.gz
	@-$(foreach APP,$(APPS), if [ -d src/$(APP) ]; then $(MAKE) -C src/$(APP) clean; fi;)

install:
	@if [ -d bin ]; then \
		echo "Installing compiled applications in $(INSTALLDIR)"; \
		cp -rf bin/* $(INSTALLDIR); \
	fi
	@if [ -d lib ]; then \
		echo "Installing libraries in $(LIBDIR)"; \
		echo "Note: You may need to add $(LIBDIR) to your library search path"; \
		cp -rf lib/* $(LIBDIR); \
	fi
	@echo "Setting up logging directory $(LOGDIR)"
	@mkdir -p $(LOGDIR)
	@chmod 666 $(LOGDIR)
	@echo "Installation complete."

doc: manual
manual: doc/manual/dpsmanual.tex
	@cd doc/manual; pdflatex dpsmanual.tex > /dev/null; \
		mv dpsmanual.pdf ../../; cd ../../

tar: manual
	@make -s clean
	@echo "Generating tarball..."
	@if [ -h `cat VERSION` ]; then rm `cat VERSION`; fi
	@ln -s . `cat VERSION`
	@tar -h --exclude `cat VERSION`/`cat VERSION` --exclude-from tar-exclude -cvf `cat VERSION | sed 's/-/_/g'`.tar `cat VERSION` > /dev/null
	@rm `cat VERSION`
	@gzip `cat VERSION | sed 's/-/_/g'`.tar
	@echo "Created ./`cat VERSION | sed 's/-/_/g'`.tar.gz"
