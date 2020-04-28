#include "parser.h"

Parser* parserFactory(ParserType type) {
    Parser *p;
    switch(type) {
        case ParserType::Bison:
            p = new BisonParser;
            break;
#ifdef EXTENDED_FEATURE
        case ParserType::CyParser:
            p = new CyParser;
            break;
#endif
    }
    return p;
}
