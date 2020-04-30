export INCLUDE_DIR = $(shell find ../../include -mindepth 1 -type d -printf "-I %p " ) -I ../../src/base

C_SRC		= $(wildcard *.c)
CPP_SRC		= $(wildcard *.cc)
C_DEPS		= $(addprefix $(DEP_DIR)/,$(C_SRC:.c=.d))
CPP_DEPS	= $(addprefix $(DEP_DIR)/,$(CPP_SRC:.cc=.dpp))

module-$(MODULE): $(DEP_DIR) $(C_DEPS) $(CPP_DEPS)
	$(MAKE) -f ../build.mk MODULE=$(MODULE)

$(C_DEPS): $(DEP_DIR)/%.d : %.c
	@$(C_COMPILER) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ_DIR)/$(^:.c=.o) $^

$(CPP_DEPS): $(DEP_DIR)/%.dpp : %.cc
	@$(CPP_COMPILER) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ_DIR)/$(^:.cc=.o) $^

$(DEP_DIR):
	$Qmkdir -p $@
