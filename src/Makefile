INCLUDE_DIR += -I ../include

.INTERMEDIATE : $(DEP_FILES)

SRC_FILES = $(wildcard *.cc)
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cc=.d))

src: $(DEP_FILES) build

$(DEP_FILES): $(DEP)/%.d : %.cc
	$(CPP_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ)/$(^:.cc=.o) $^

build:
	$(MAKE) -f build.mk
