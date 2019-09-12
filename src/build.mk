SRC_FILES = $(wildcard *.cpp)
OBJ_FILES = $(addprefix $(OBJ)/,$(SRC_FILES:.cpp=.o))
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cpp=.d))

objs: $(OBJ_FILES)

$(OBJ_FILES):
	$(CPP_COMPILE) $(INCLUDE_DIR) -c -o $@ $<

include $(DEP_FILES)
