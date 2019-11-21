SRC_FILES = $(wildcard *.cpp)
OBJ_FILES = $(addprefix $(OBJ)/,$(SRC_FILES:.cpp=.o))
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cpp=.d))

scanner-build: $(OBJ_FILES) $(OBJ_FILES)

$(OBJ_FILES):
	$(CY_COMPILE) $(INCLUDE_DIR) -c -o $@ $<
ifeq ($(MODE),coverage)
	ln -fsr $< $(OBJ)/
endif

include $(DEP_FILES)
