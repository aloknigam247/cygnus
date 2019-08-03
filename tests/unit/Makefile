.PHONY: all $(wildcard *)

all: $(warning echo $(wildcard *)) $(wildcard *)

$(wildcard *):
	echo $@
	echo ${CYGNUS_HOME}/tools/gen-make -d $@

Makefile:
