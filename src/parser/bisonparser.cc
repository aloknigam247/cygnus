#include "bisonparser.h"

/* Bison entry function */
extern "C" struct CylGrammar* CylBisonEntry(const char*);

BisonDigest* BisonParser::parse(std::string file) {
    BisonDigest *d = new BisonDigest;
    d->set_data(CylBisonEntry(file.c_str()));
    return d;
}
