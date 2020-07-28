#ifdef EXTENDED_FEATURE
#include "bisonparser.h"

/* Bison entry function */
extern "C" void* CylBisonEntry(const char*);

Digest* BisonParser::parse(std::string file) {
    Digest *d = new Digest;
    d->set_data(CylBisonEntry(file.c_str()));
    return d;
}
#endif
