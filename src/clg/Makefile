export INCLUDE_DIR += -I . \
	-I ../../include/base \
	-I ../../include/clg \
	-I ../../include/compiler \
	-I ../../include/scanner \
	-I ../base/tcc

SRC_FILES = $(wildcard *.cc)
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cc=.d))

clg: $(DEP) $(OBJ) $(DEP_FILES) $(OBJ)/clg.flex.o $(OBJ)/clg.tab.o build

$(DEP) $(OBJ):
	$Qmkdir -p $@

$(DEP_FILES): $(DEP)/%.d : %.cc
	$(CY_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ)/$(^:.cc=.o) $^

build:
	$(MAKE) -f build.mk

$(OBJ)/clg.flex.o: clg.flex.c
	gcc -fdiagnostics-color -c clg.flex.c -o $@

$(OBJ)/clg.tab.o: clg.tab.c
	gcc -fdiagnostics-color -c clg.tab.c -o $@

clg.flex.c: clg.l clg.tab.h
	flex -o clg.flex.c clg.l

clg.tab.c: clg.y
	bison -d clg.y

clg.l:
	echo "clg.l"
