#---------- Configs ---------- #
.DEFAULT_GOAL = compile
.PHONY: src compile
Q	:= @

#---------- Modes ----------# 
ifeq ($(MODE),coverage)
CPP_FLAGS 	+= --coverage -g
# Using ver 7 as lcov does not support ver 9 gcno file dump
CXX          = g++-7
else ifeq ($(MODE),debug)
CPP_FLAGS 	+= -g
else ifeq ($(MODE),memory)
CPP_FLAGS 	+= -g
else ifeq ($(MODE),perf)
CPP_FLAGS 	+= -pg
else ifeq ($(MODE),release)
CPP_FLAGS 	+= -O
else ifeq ($(MODE),sanitize)
CPP_FLAGS 	+= -g -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
			-fsanitize=address -fsanitize-address-use-after-scope -fsanitize=float-cast-overflow\
			-fsanitize=leak -fsanitize=undefined -fsanitize-undefined-trap-on-error
else ifndef MODE
MODE=debug
CPP_FLAGS 	+= -g
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
export CPP_FLAGS += -std=c++11 -fdiagnostics-color
ifdef STRICT
	CPP_FLAGS += -pedantic -Wall -Walloc-zero -Wcast-align -Wcast-qual -Wconversion\
				-Wduplicated-branches -Wduplicated-cond -Weffc++ -Wextra -Wfloat-equal -Wformat=2\
				-Winline -Wlogical-op -Wmissing-include-dirs -Woverloaded-virtual -Wshadow\
				-Wstrict-overflow=5 -Wstringop-overflow=2 -Wsuggest-attribute=const\
				-Wswitch-default -Wswitch-enum -Wunused -Wunused-macros
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
$(MOD_EXE):  $(addprefix $(OBJ)/,$(notdir $(subst .cpp,.o,$(wildcard src/*.cpp))))
	$(CPP_COMPILE) -o $@ $^

clean:
	$Qecho "cleaning ..."
	rm -rf $(BLD_DIR)
