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

    lex_writer->write((CylGrammar*)d->get_data(), cyl_file);
    parse_writer->write((CylGrammar*)d->get_data(), cyl_file);
}

/*
    std::string file_base = lang_file.substr(0, lang_file.size()-4);
    size_t pos = file_base.rfind('/');
    if(pos == std::string::npos)
        pos = 0;
    else
        pos++;
    std::cout << "file_base: " << file_base << '\n';
    std::cout << "pos: " << pos << '\n';
    std::cout << "size: " << file_base.size() << '\n';

    std::string file_stem = file_base.substr(pos, file_base.size()-pos);
    generateBison(g, file_base);
    generateFlex(g->variable_head, file_base, file_stem);
*/
