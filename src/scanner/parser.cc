#include "parser.h"

Parser* parserFactory(ParserType type) {
    switch(type) {
        case ParserType::Bison:
            return new BisonParser;
#ifdef EXTENDED_FEATURE
        case ParserType::CyParser:
            return new CyParser;
#endif
    }
}
