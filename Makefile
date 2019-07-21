# Top Makefile

include recipe/config.mk
include recipe/procs.mk
include ext/common.mk

INC_LIBS = ## libs needed for .o --> executable

DIRS := src

.PHONY: $(DIRS) run $(EXT_LIBS)

all: $(DIRS) $(EXECUTABLE)

$(DIRS):
	@$(MAKE) $(MAKE_FLAGS) -C $@
	@touch Makefile

OBJ_FILE = $(wildcard $(OBJ)/*)

$(EXECUTABLE): $(OBJ_FILE)
ifeq ($(OBJ_FILE),)		# First case: When obj files are not there restart Makefile
	@$(MAKE) $(MAKE_FLAGS) -f Makefile

else									# Second case: When obj files are generated then compile them
	$(CXX) -L $(LIB_DIR) -o $@ $^ $(INC_LIBS)

endif
