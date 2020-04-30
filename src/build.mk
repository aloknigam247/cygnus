C_SRC	= $(wildcard *.c)
CPP_SRC	= $(wildcard *.cc)
OBJS	= $(addprefix $(OBJ_DIR)/,$(C_SRC:.c=.o)) $(addprefix $(OBJ_DIR)/,$(CPP_SRC:.cc=.o))
DEPS	= $(addprefix $(DEP_DIR)/,$(C_SRC:.c=.d)) $(addprefix $(DEP_DIR)/,$(CPP_SRC:.cc=.dpp))

DEFINES	= -DVERSION=$(shell cat ../../.internal/version)

build-$(MODULE): $(OBJ_DIR) $(OBJS)

$(OBJS):	# It should be empty else it will override rule from depends file
ifeq (, $(wildcard $(@F:.o=.c)))
	$(C_COMPILE) $(DEFINES) $(INCLUDE_DIR) -c -o $@ $<
else
	$(CPP_COMPILE) $(DEFINES) $(INCLUDE_DIR) -c -o $@ $<
endif
ifeq ($(MODE),coverage)
	ln -fsr $< $(OBJ_DIR)/
endif

$(OBJ_DIR):
	$Qmkdir -p $@

include $(DEPS)
