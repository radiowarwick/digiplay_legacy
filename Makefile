APPS	=	audio admin studio_play studio_manage sueplay suesched playin

all: $(APPS) 

%:
	@if [ -d src/$@ ]; then $(MAKE) -C src/$@; fi;

clean:
	@echo "Cleaning source tree"
	@rm -rf bin lib src/*.o
	@-$(foreach APP,$(APPS), if [ -d src/$(APP) ]; then $(MAKE) -C src/$(APP) clean; fi;)
