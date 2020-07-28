#ifdef EXTENDED_FEATURE
#include "parser.h"

enum class ParserType {
    Bison,
    CyParser
};

Parser *parserFactory(ParserType t);
#endif
