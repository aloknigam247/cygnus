#ifdef EXTENDED_FEATURE
#include "parserfactory.h"
#include "bisonparser.h"
#include "cyparser.h"

Parser* parserFactory(ParserType type) {
    Parser *p = nullptr;
    switch(type) {
        case ParserType::Bison:
            p = new BisonParser;
        case ParserType::CyParser:
            p = new CyParser;
    }
    return p;
}
#endif
