export INCLUDE_DIR += -I . -I ../../include -I ../../include/utils -I tcc

SRC_FILES = $(wildcard *.cpp)
DEP_FILES = $(addprefix $(DEP)/,$(SRC_FILES:.cpp=.d))

all: $(DEP) $(OBJ) $(DEP_FILES) build

$(DEP) $(OBJ):
	$Qmkdir -p $@

$(DEP_FILES): $(DEP)/%.d : %.cpp
	$(CY_COMPILE) $(INCLUDE_DIR) -MM -MF $@ -MT $(OBJ)/$(^:.cpp=.o) $^

build:
	$(MAKE) -f build.mk
