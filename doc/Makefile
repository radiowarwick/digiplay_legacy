.PHONY : clean

default: all

all: manual doxygen

clean:
	@make -C manual clean
	@rm -rf code
	
manual:
	@make -C manual
	
doxygen:
	doxygen doxygen.conf