SRC_FILES = $(wildcard *.cc)
OBJ_FILES = $(addprefix $(OBJ)/,$(SRC_FILES:.cc=.o))
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cc=.d))

DEFINES= -DVERSION=$(shell cat ../../.version)

base-build: $(OBJ_FILES) $(OBJ_FILES)

$(OBJ_FILES):
	$(CY_COMPILE) $(DEFINES) $(INCLUDE_DIR) -c -o $@ $<
ifeq ($(MODE),coverage)
	ln -fsr $< $(OBJ)/
endif

include $(DEP_FILES)
