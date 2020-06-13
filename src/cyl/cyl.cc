#include "cyl.h"
#include "cyl-grammar.h"

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

extern "C" void* CylBisonEntry(const char*);

Cyl::Cyl(ScannerType t) {
    ScannerFactory f(t);
    parser = f.giveParser();
    lex_writer = f.giveLexWriter();
    parse_writer = f.giveParseWriter();
    ((BisonParser*)parser)->set_entry(CylBisonEntry);
}

void Cyl::generateParser(std::string cyl_file) {
    Digest *d = parser->parse(cyl_file);

    CylGrammar *data = d->get_data();

    lex_writer->write(data, cyl_file);
    parse_writer->write(data, cyl_file);
}
