#ifdef EXTENDED_FEATURE
#include "bisonparser.h"

enum class ParserType {
    Bison,
    CyParser
};

Parser *parserFactory(ParserType t);
#endif
