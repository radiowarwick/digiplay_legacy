#TOOLS := "find . -maxdepth 1 -name "Makefile.*" -type f  | xargs | sed -e 's/.\/Makefile.//g'"

%:
	@if [ -e Makefile.$@ ]; then $(MAKE) -f Makefile.$@; fi;

all:
	@find . -maxdepth 1 -name "Makefile.*" -type f -exec make --no-print-directory -f {} \;

clean:
	@find . -maxdepth 1 -name "Makefile.*" -type f -exec make --no-print-directory -f {} clean \;
