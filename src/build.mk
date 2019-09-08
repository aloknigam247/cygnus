INCLUDE_DIR += -I ../include
SRC_FILES = $(wildcard *.cc)
OBJ_FILES = $(addprefix $(OBJ)/,$(SRC_FILES:.cc=.o))
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cc=.d))

objs: $(OBJ_FILES)

$(OBJ_FILES):
	$(CPP_COMPILE) $(INCLUDE_DIR) -c -o $@ $<

include $(DEP_FILES)
