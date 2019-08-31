########### Path Configurations ########### 
export SOURCE_DIR   := $(CURDIR)
export BUILD_DIR	:= $(SOURCE_DIR)/build
export BIN          := $(BUILD_DIR)/bin
export DEP          := $(BUILD_DIR)/dep
export OBJ          := $(BUILD_DIR)/obj
export LIB_DIR      := $(SOURCE_DIR)/lib
export OUT_DIR      := $(SOURCE_DIR)/out
export EXECUTABLE   := $(BIN)/cygnus
export EXT_PATH 		:= $(SOURCE_DIR)/ext
export EXT_LIBS     := 	# Path of external libs for linking filled in ext/*/options.mk

########### Local Configurations ###########
DUMP         := $(BIN) $(DEP) $(OBJ) $(BUILD_DIR) $(LIB_DIR)	# Targets producing files which needs to be cleaned on make clean

########### Compile Flags ########### 
export CPP_FLAGS = -std=c++11
ifdef STRICT
	CPP_FLAGS += -Wall -Walloc-zero -Wchkp -Wduplicated-branches -Weffc++ -Werror -Wextra -Wformat -Winline -Wmissing-include-dirs -Woverloaded-virtual -Wstrict-overflow=5 -Wstringop-overflow -Wsuggest-attribute=const -Wswitch-default -Wswitch-enum -Wunused -Wunused-macros
endif
export CPP_COMPILE = $(CXX) $(CPP_FLAGS) $$(INCLUDE_DIR) -L $(LIB_DIR)	# $$(INCLUDE_DIR) is passed to sub-make to fill and use

########### Make Flags ########### 
export MAKE_FLAGS :=--no-print-directory 

########### Default Target ###########
all: $(DUMP)

########## Regular Targets ###########
$(DUMP):
	mkdir -p $@

clean:
	rm -rf $(DUMP)

