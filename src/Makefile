MODULES := base compiler scanner

.PHONY: $(MODULES)

all: $(MODULES)

$(MODULES):
	$(MAKE) -C $@ DEP=$(DEP)/$@ OBJ=$(OBJ)/$@
