# Compilation of all external directories

sub_dirs = $(wildcard ext/*)	# list of sub dirs

# Each sub dir should be supplied with options.mk
-include $(addsuffix /options.mk,$(sub_dirs))	# include options from all sub directories

lib_list = $(foreach lib_dir,$(EXT_LIBS), $(wildcard $(lib_dir)/lib*))	# list of all libs available in external directory
lib_name = $(foreach lib,$(lib_list),$(call filename,$(lib)))						# list of libnames
lib_link = $(addprefix $(LIB_DIR)/,$(lib_name))													# path of linked lib

all: $(lib_link)	# include lib to be processed with default target

$(lib_link):
	ln -frs $(filter %$(strip $(call filename,$@)),$(lib_list)) $(LIB_DIR)
