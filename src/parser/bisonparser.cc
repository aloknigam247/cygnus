#include "parser.h"

Digest* BisonParser::parse(std::string file) {
    Digest *d = new Digest;
    d->set_data(bison_entry(file.c_str()));
    return d;
}
