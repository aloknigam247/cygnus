#ifdef EXTENDED_FEATURE
#include "cyl.h"
#include "cylgrammar.h"
#include "parserfactory.h"
#include "bisonparser.h"

Parser* ScannerFactory::giveParser() {
    Parser *p;
    switch(type) {
        case Cygnus:
            p = parserFactory(ParserType::CyParser);
            break;
        case GNU:
            p = parserFactory(ParserType::Bison);
            break;
    }
    return p;
}

Writer* ScannerFactory::giveParseWriter() {
    Writer *w;
    switch(type) {
        case Cygnus:
            w = writerFactory(WriterType::CyParse);
            break;
        case GNU:
            w = writerFactory(WriterType::Bison);
            break;
    }
    return w;
}

Writer* ScannerFactory::giveLexWriter() {
    Writer *w;
    switch(type) {
        case Cygnus:
            w = writerFactory(WriterType::CyLex);
            break;
        case GNU:
            w = writerFactory(WriterType::Flex);
            break;
    }
    return w;
}

Cyl::Cyl(ScannerType t) {
    ScannerFactory f(t);
    parser = f.giveParser();
    lex_writer = f.giveLexWriter();
    parse_writer = f.giveParseWriter();
}

void Cyl::generateParser(std::string cyl_file) {
    Digest *d = parser->parse(cyl_file);

    CylGrammar *data = (CylGrammar*)d->get_data();

    lex_writer->write(data, cyl_file);
    parse_writer->write(data, cyl_file);
}
#endif
