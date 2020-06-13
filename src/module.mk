export INCLUDE_DIR = $(shell find ../../include -mindepth 1 -type d -printf "-I %p " ) -I ../../src/base

BISON_FILES	= $(wildcard *.y)
BISON_SRC	= $(subst .y,-bison.c,$(BISON_FILES))

FLEX_FILES	= $(wildcard *.l)
FLEX_SRC	= $(subst .l,-flex.c,$(FLEX_FILES))

C_SRC		= $(wildcard *.c)
CPP_SRC		= $(wildcard *.cc)

C_DEPS		= $(addprefix $(DEP_DIR)/,$(C_SRC:.c=.d))
CPP_DEPS	= $(addprefix $(DEP_DIR)/,$(CPP_SRC:.cc=.dpp))

module-$(MODULE): $(DEP_DIR) $(BISON_SRC) $(FLEX_SRC) $(C_DEPS) $(CPP_DEPS)
	$(MAKE) -f ../build.mk MODULE=$(MODULE)

$(BISON_SRC): %-bison.c: %.y
	bison --defines=$(@:.c=.h) -o $@ $^

$(FLEX_SRC): %-flex.c: %.l
	flex -o $@ $^

$(C_DEPS): $(DEP_DIR)/%.d : %.c
	@$(C_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ_DIR)/$(^:.c=.o) $^

$(CPP_DEPS): $(DEP_DIR)/%.dpp : %.cc
	@$(CPP_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ_DIR)/$(^:.cc=.o) $^

$(DEP_DIR):
	$Qmkdir -p $@
