#include <assert.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "tsparser.h"
#include "tree_sitter/api.h"
#include <dlfcn.h>

const TSLanguage *load_cpp_library() {
  // Get the handle to the library.
  void *handle = dlopen("./cpp.so", RTLD_LAZY);
  if (handle == NULL) {
    fprintf(stderr, "Could not open library: %s\n", dlerror());
    return NULL;
  }

  // Get the address of the function.
  void *tree_sitter_lang = dlsym(handle, "tree_sitter_cpp");
  if (tree_sitter_lang == NULL) {
    fprintf(stderr, "Could not find function: %s\n", dlerror());
    return NULL;
  }

  return (const TSLanguage*)tree_sitter_lang;
}

extern "C" const TSLanguage* tree_sitter_cpp();

void TsParser::parse(std::string file) {
    // Create a parser.
    TSParser *parser = ts_parser_new();

    // Set the parser's language (CPP in this case).
    bool result = ts_parser_set_language(parser, tree_sitter_cpp());

    // Build a syntax tree based on source code stored in a string.
    std::ifstream infile(file);
    if (!infile.is_open()) {
        std::cout << "Error in opening file " << file;
        return;
    }

    infile.seekg(0, std::ios::end);
    int file_size = infile.tellg();

    char* source_code = new char[file_size + 1];

    infile.seekg(0, std::ios::beg);
    infile.read(source_code, file_size);
    infile.close();
    source_code[file_size] = '\0';

    TSTree *tree = ts_parser_parse_string(parser, NULL, source_code, strlen(source_code));

    // Get the root node of the syntax tree.
    TSNode root_node = ts_tree_root_node(tree);

    // Get some child nodes.
    TSNode array_node = ts_node_named_child(root_node, 0);
    TSNode number_node = ts_node_named_child(array_node, 0);

    // Print the syntax tree as an S-expression.
    char *string = ts_node_string(root_node);
    printf("Syntax tree: %s\n", string);

    // Free all of the heap-allocated memory.
    free(string);
    delete[] source_code;
    ts_tree_delete(tree);
    ts_parser_delete(parser);
}
