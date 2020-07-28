#---------- Configs ----------#
.DEFAULT_GOAL = compile
.PHONY: compile lang src
export Q	:= @

#---------- Modes ----------# 
export CPP_COMPILER	= g++
export C_COMPILER	= gcc

ifeq ($(MODE),coverage)
CPP_COMPILER	= g++
C_COMPILER		= gcc
COMPILER_FLAGS	+= --coverage -ggdb3

else ifeq ($(MODE),debug)
COMPILER_FLAGS	+= -ggdb3

else ifeq ($(MODE),memory)
COMPILER_FLAGS	+= -ggdb3

else ifeq ($(MODE),perf)
COMPILER_FLAGS	+= -ggdb3

else ifeq ($(MODE),release)
COMPILER_FLAGS	+= -Ofast

else ifeq ($(MODE),sanitize)
COMPILER_FLAGS	+= -ggdb3 -D_FORTIFY_SOURCE=2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
				-fsanitize=address -fsanitize-address-use-after-scope -fsanitize=float-cast-overflow\
				-fsanitize=leak -fsanitize=undefined -fsanitize-undefined-trap-on-error

else ifeq ($(MODE),clean)
.DEFAULT_GOAL = clean

else ifndef MODE
MODE=debug
COMPILER_FLAGS 	+= -ggdb3

else
$(error unknown MODE '$(MODE)')
endif

#---------- Path Configurations ----------# 
BLD_DIR	:= $(CURDIR)/build
BIN_DIR	:= $(BLD_DIR)/bin/$(MODE)
DEP_DIR	:= $(BLD_DIR)/dep
OBJ_DIR	:= $(BLD_DIR)/obj/$(MODE)
SRC_GEN	:= $(BLD_DIR)/src
EXE		:= $(BIN_DIR)/cygnus-$(MODE)
DUMP	:= $(BIN_DIR) $(SRC_GEN)
LINK	:= $(BLD_DIR)/bin/cygnus

export DEP_DIR OBJ_DIR SRC_GEN

#---------- Compile Flags ----------# 
COMPILER_FLAGS	+= -fdiagnostics-color
ifeq ($(STRICT),yes)
COMPILER_FLAGS	+= -pedantic -Wall -Walloc-zero -Wcast-align -Wcast-qual -Wconversion\
				-Wduplicated-branches -Wduplicated-cond -Weffc++ -Wextra -Wfloat-equal -Wformat=2\
				-Winline -Wlogical-op -Wmissing-include-dirs -Woverloaded-virtual -Wshadow\
				-Wstrict-overflow=5 -Wstringop-overflow=2 -Wsuggest-attribute=const\
				-Wswitch-default -Wswitch-enum -Wunused -Wunused-macros
endif
export C_COMPILE	:= $(C_COMPILER) -std=c11 $(COMPILER_FLAGS)
export CPP_COMPILE	:= $(CPP_COMPILER) -std=c++11 $(COMPILER_FLAGS)

#---------- Make Flags ----------#
MAKE_FLAGS	+= --no-print-directory 
export MAKE	= $Qmake $(MAKE_FLAGS)

#---------- Rules ----------#
compile: $(DUMP) src $(LINK)

$(DUMP):
	$Qmkdir -p $@

src:
	$(MAKE) -C $@

$(LINK): $(EXE)
	ln -sfr $< $@

$(EXE): $(subst src,$(OBJ_DIR),$(subst .cc,.co,$(wildcard src/*/*.cc))) $(subst src,$(OBJ_DIR),$(subst .c,.o,$(wildcard src/*/*.c))) $(subst build/src,$(OBJ_DIR),$(subst .c,.o,$(wildcard build/src/*/*.c)))
	$(CPP_COMPILE) -o $@ $^

clean:
	$Qecho "cleaning ..."
	rm -rf $(BLD_DIR)
