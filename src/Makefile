INCLUDE_DIR += -I ../include

SRC_FILES = $(wildcard *.cc)
OBJ_FILES = $(addprefix $(OBJ)/,$(SRC_FILES:.cc=.o))
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cc=.d))

src: $(DEP_FILES) $(OBJ_FILES)

$(DEP_FILES): $(DEP)/%.d : %.cc
	$(CPP_COMPILE) -MM -MF $@ -MT $(OBJ)/$(^:.cc=.o) $^
	@touch Makefile

$(OBJ_FILES):
	$(CPP_COMPILE) -c -o $@ $<

-include $(DEP_FILES)
