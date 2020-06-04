#include "parser.h"

extern "C" struct Grammar *digest(const char *file_name);

Grammar* BisonParser::parse(std::string file) {
    return digest(file.c_str());
}
