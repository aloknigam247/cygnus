export INCLUDE_DIR += -I . \
	-I ../../include/base \
	-I ../../include/compiler \
	-I ../../include/scanner \
	-I tcc

SRC_FILES = $(wildcard *.cc)
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cc=.d))

compiler: $(DEP) $(OBJ) $(DEP_FILES) build

$(DEP) $(OBJ):
	$Qmkdir -p $@

$(DEP_FILES): $(DEP)/%.d : %.cc
	$(CY_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ)/$(^:.cc=.o) $^

build:
	$(MAKE) -f build.mk
