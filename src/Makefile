MODULES := base clg compiler scanner

.PHONY: $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) -C $@ DEP=$(DEP)/$@ OBJ=$(OBJ)/$@ BIN=$(BLD_DIR)/bin
