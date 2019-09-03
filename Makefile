# Top Makefile

include recipe/procs.mk

#---------- Configs ---------- #
.DEFAULT_GOAL = compile
.PHONY: src compile
Q	:= @

#---------- Modes ----------# 
ifeq ($(MODE),debug)
MODE = debug
else ifeq ($(MODE),release)
MODE = release
else
MODE = debug
$(info debug as defaut mode)
endif

#---------- Path Configurations ----------# 
BLD_DIR	:= $(CURDIR)/build
BIN		:= $(BLD_DIR)/bin/$(MODE)
DEP		:= $(BLD_DIR)/dep/$(MODE)
OBJ		:= $(BLD_DIR)/obj/$(MODE)
MOD_EXE	:= $(BIN)/cygnus-$(MODE)
DUMP 	:= $(BIN) $(OBJ) $(DEP)
EXE 	:= $(BIN)/cygnus

export OBJ DEP

#---------- Compile Flags ----------# 
export CPP_FLAGS = -std=c++11
ifdef STRICT
	CPP_FLAGS += -Wall -Walloc-zero -Wchkp -Wduplicated-branches -Weffc++ -Wextra -Wformat -Winline -Wmissing-include-dirs -Woverloaded-virtual -Wstrict-overflow=5 -Wstringop-overflow -Wsuggest-attribute=const -Wswitch-default -Wswitch-enum -Wunused -Wunused-macros
endif
export CPP_COMPILE = $(CXX) $(CPP_FLAGS) $$(INCLUDE_DIR)	# $$(INCLUDE_DIR) is passed to sub-make to fill and use

#---------- Make Flags ----------#
export MAKE			 = $Qmake $(MAKE_FLAGS)
export MAKE_FLAGS	:= --no-print-directory 

#---------- Rules ----------#
compile: $(DUMP) src $(EXE)

$(DUMP):
	$Qmkdir -p $@

src:
	$(MAKE) -C $@

$(EXE): $(MOD_EXE)
	ln -sfr $< $@

$(MOD_EXE):  $(addprefix $(OBJ)/,$(notdir $(subst .cc,.o,$(wildcard src/*.cc))))
	$(CXX) -o $@ $^

clean:
	rm -rf $(BLD_DIR)
