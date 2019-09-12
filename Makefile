#---------- Configs ---------- #
.DEFAULT_GOAL = compile
.PHONY: src compile
Q	:= @

#---------- Modes ----------# 
ifeq ($(MODE),coverage)
CPP_FLAGS 	+= --coverage -g3
MODE=coverage
else ifeq ($(MODE),debug)
CPP_FLAGS 	+= -g3
MODE=debug
else ifeq ($(MODE),release)
CPP_FLAGS 	+= -O
MODE=release
else ifndef MODE
CPP_FLAGS 	+= -g3
MODE=debug
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
	CPP_FLAGS += -Wall -Wchkp -Weffc++ -Wextra -Wformat -Winline -Wmissing-include-dirs -Woverloaded-virtual -Wstrict-overflow=5 -Wsuggest-attribute=const -Wswitch-default -Wswitch-enum -Wunused -Wunused-macros
# -Walloc-zero -Wduplicated-branches -Wstringop-overflow disabling for now as circleci doesn't have g++ 7.4
endif
export CPP_COMPILE := $(CXX) $(CPP_FLAGS)	# $$(INCLUDE_DIR) is passed to sub-make to fill and use

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
	rm -rf $(BLD_DIR)
