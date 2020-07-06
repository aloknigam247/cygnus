.DEFAULT_GOAL := module-$(MODULE)

export INCLUDE_DIR := $(shell find $(CYGNUS_HOME)/include -mindepth 1 -type d -printf "-I %p " ) -I ../../src/base

BISON_FILES	= $(wildcard *.y)
FLEX_FILES	= $(wildcard *.l)

ifeq (, $(or $(BISON_FILES), $(FLEX_FILES)))
AUTOGEN_TARGETS :=
AUTOGEN_BLD     :=
BISON_DEPS      :=
FLEX_DEPS       :=
else
BISON_SRC	= $(addprefix $(SRC_GEN)/$(MODULE)/,$(subst .y,-bison.c,$(BISON_FILES)))
FLEX_SRC	= $(addprefix $(SRC_GEN)/$(MODULE)/,$(subst .l,-flex.c,$(FLEX_FILES)))

BISON_DEPS  = $(addprefix $(DEP_DIR)/,$(notdir $(BISON_SRC:.c=.d)))
FLEX_DEPS   = $(addprefix $(DEP_DIR)/,$(notdir $(FLEX_SRC:.c=.d)))

SRC_MOD_DIR     := $(SRC_GEN)/$(MODULE)
AUTOGEN_TARGETS := $(SRC_MOD_DIR) $(BISON_SRC) $(FLEX_SRC) $(BISON_DEPS) $(FLEX_DEPS)
AUTOGEN_BLD     := $(MAKE) -C $(SRC_MOD_DIR) -f ../../../src/build.mk MODULE=$(MODULE)

$(SRC_MOD_DIR):
	mkdir -p $@

$(BISON_DEPS) $(FLEX_DEPS): $(DEP_DIR)/%.d: $(SRC_MOD_DIR)/%.c
	$(C_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(subst $(MODE),\$${MODE},$(OBJ_DIR))/$(notdir $(^:.c=.o)) $^

$(BISON_SRC): $(SRC_MOD_DIR)/%-bison.c: %.y
	bison --defines=$(@:.c=.h) -o $@ $^

$(FLEX_SRC): $(SRC_MOD_DIR)/%-flex.c: %.l
	flex -o $@ $^
endif

C_SRC		= $(wildcard *.c)
CPP_SRC		= $(wildcard *.cc)

C_DEPS		= $(addprefix $(DEP_DIR)/,$(C_SRC:.c=.d))
CPP_DEPS	= $(addprefix $(DEP_DIR)/,$(CPP_SRC:.cc=.dpp))


module-$(MODULE): $(DEP_DIR) $(AUTOGEN_TARGETS) $(C_DEPS) $(CPP_DEPS)
	$(AUTOGEN_BLD)
	$(MAKE) -f ../build.mk MODULE=$(MODULE)

$(C_DEPS): $(DEP_DIR)/%.d : %.c
	$(C_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(subst $(MODE),\$${MODE},$(OBJ_DIR))/$(^:.c=.o) $^

$(CPP_DEPS): $(DEP_DIR)/%.dpp : %.cc
	$(CPP_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(subst $(MODE),\$${MODE},$(OBJ_DIR))/$(^:.cc=.co) $^

$(DEP_DIR):
	$Qmkdir -p $@
