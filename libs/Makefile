MAKEOVERRIDES =
MODULES := tree-sitter

libs: $(LIB_DIR)/tree-sitter.a

$(LIB_DIR)/tree-sitter.a: tree-sitter/libtree-sitter.a
	cp tree-sitter/libtree-sitter.a $(LIB_DIR)/tree-sitter.a
	cp -r tree-sitter/lib/include/tree_sitter $(INC_DIR)/

tree-sitter/libtree-sitter.a:
	cd tree-sitter; export MAKEFLAGS="";make $(MAKE_FLAGS) MAKEFLAGS=
