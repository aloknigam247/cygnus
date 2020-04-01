MODULES := $(sort $(shell find -maxdepth 1 -mindepth 1 -type d -printf '%f '))

.PHONY: $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) -f ../module.mk -C $@ MODULE=$@ DEP_DIR=$(DEP_DIR)/$@ OBJ_DIR=$(OBJ_DIR)/$@
