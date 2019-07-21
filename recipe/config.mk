########### Path Configurations ########### 
export SOURCE_DIR   := $(CURDIR)
export BUILD_DIR		:= $(SOURCE_DIR)/build
export BIN          := $(BUILD_DIR)/bin
export DEP          := $(BUILD_DIR)/dep
export OBJ          := $(BUILD_DIR)/obj
export LIB_DIR      := $(SOURCE_DIR)/lib
export OUT_DIR      := $(SOURCE_DIR)/out
export EXECUTABLE   := $(BIN)/exe
export EXT_PATH 		:= $(SOURCE_DIR)/ext
export EXT_LIBS     := 	# Path of external libs for linking filled in ext/*/options.mk

########### Local Configurations ###########
DUMP         := $(BIN) $(DEP) $(OBJ) $(BUILD_DIR) $(LIB_DIR)	# Targets producing files which needs to be cleaned on make clean

########### Compile Flags ########### 
export CPP_COMPILE = $(CXX) $$(INCLUDE_DIR) -L $(LIB_DIR)	# $$(INCLUDE_DIR) is passed to sub-make to fill and use

########### Make Flags ########### 
export MAKE_FLAGS :=--no-print-directory 

########### Default Target ###########
all: $(DUMP)

########## Regular Targets ###########
$(DUMP):
	mkdir -p $@

clean:
	rm -rf $(DUMP)

