﻿MAKEOVERRIDES =
MODULES := tree-sitter

external: $(LIB_DIR)/libtree-sitter.a

$(LIB_DIR)/libtree-sitter.a: tree-sitter/libtree-sitter.a
	cp tree-sitter/libtree-sitter.a $(LIB_DIR)/
	cp -r tree-sitter/lib/include/tree_sitter $(INC_DIR)/

tree-sitter/libtree-sitter.a:
	cd tree-sitter; export MAKEFLAGS="";make $(MAKE_FLAGS) MAKEFLAGS=
