#---------- Configs ---------- #
.DEFAULT_GOAL = compile
.PHONY: src compile
Q	:= @

#---------- Modes ----------# 
ifeq ($(MODE),coverage)
CPP_FLAGS 	+= --coverage -g
else ifeq ($(MODE),debug)
CPP_FLAGS 	+= -g
else ifeq ($(MODE),memory)
CPP_FLAGS 	+= -g
else ifeq ($(MODE),perf)
CPP_FLAGS 	+= -pg
else ifeq ($(MODE),release)
CPP_FLAGS 	+= -O
else ifeq ($(MODE),sanitize)
CPP_FLAGS 	+= -g -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -fsanitize=address -fsanitize-address-use-after-scope -fsanitize-coverage=trace-pc -fsanitize=float-cast-overflow -fsanitize=leak -fsanitize=undefined -fsanitize-undefined-trap-on-error
else ifndef MODE
CPP_FLAGS 	+= -g
$(info debug as defaut mode)
else
$(error unknown MODE '$(MODE)')
endif

#---------- Path Configurations ----------# 
BLD_DIR	:= $(CURDIR)/build
BIN		:= $(BLD_DIR)/bin/$(MODE)
DEP		:= $(BLD_DIR)/dep/$(MODE)
OBJ		:= $(BLD_DIR)/obj/$(MODE)
MOD_EXE	:= $(BIN)/cygnus-$(MODE)
DUMP 	:= $(BIN) $(OBJ) $(DEP)
EXE 	:= $(BLD_DIR)/bin/cygnus

export OBJ DEP

#---------- Compile Flags ----------# 
export CPP_FLAGS += -std=c++11
ifdef STRICT
	CPP_FLAGS += -Wall -Walloc-zero -Wduplicated-branches -Weffc++ -Wextra -Wformat -Winline -Wmissing-include-dirs -Woverloaded-virtual -Wstrict-overflow=5 -Wstringop-overflow -Wsuggest-attribute=const -Wswitch-default -Wswitch-enum -Wunused -Wunused-macros
endif
export CPP_COMPILE := $(CXX) $(CPP_FLAGS)

#---------- Make Flags ----------#
export MAKE_FLAGS	:= --no-print-directory 
export MAKE			 = $Qmake $(MAKE_FLAGS)

#---------- Rules ----------#
compile: $(DUMP) src $(EXE)

$(DUMP):
	$Qmkdir -p $@

src:
	$(MAKE) -C $@

$(EXE): $(MOD_EXE)
	ln -sfr $< $@

$(MOD_EXE):  INCLUDE_DIR=''
$(MOD_EXE):  $(addprefix $(OBJ)/,$(notdir $(subst .cc,.o,$(wildcard src/*.cc))))
	$(CPP_COMPILE) -o $@ $^

clean:
	rm -rf $(BLD_DIR)
