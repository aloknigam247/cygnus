C_SRC	= $(wildcard *.c)
CPP_SRC	= $(wildcard *.cc)
OBJS	= $(addprefix $(OBJ_DIR)/,$(C_SRC:.c=.o)) $(addprefix $(OBJ_DIR)/,$(CPP_SRC:.cc=.o))
DEPS	= $(addprefix $(DEP_DIR)/,$(C_SRC:.c=.d)) $(addprefix $(DEP_DIR)/,$(CPP_SRC:.cc=.dpp))

DEFINES	= -DVERSION=$(shell cat ../../.version)

build-$(MODULE): $(OBJ_DIR) $(OBJS)

$(OBJS):	# It should be empty else it will override rule from depends file
	$(CPP_COMPILE) $(DEFINES) $(INCLUDE_DIR) -c -o $@ $<
ifeq ($(MODE),coverage)
	ln -fsr $< $(OBJ_DIR)/
endif

$(OBJ_DIR):
	$Qmkdir -p $@

include $(DEPS)
