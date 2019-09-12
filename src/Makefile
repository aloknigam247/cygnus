export INCLUDE_DIR += -I ../include

.INTERMEDIATE : $(DEP_FILES)

SRC_FILES = $(wildcard *.cpp)
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cpp=.d))

src: $(DEP_FILES) build

$(DEP_FILES): $(DEP)/%.d : %.cpp
	$(CPP_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ)/$(^:.cpp=.o) $^

build:
	$(MAKE) -f build.mk
