#include "parser.h"
#include "writer.h"

enum ScannerType {
    Cygnus,
    GNU
};

class ScannerFactory {
    public:
    ScannerFactory(ScannerType t): type(t) {}
    Parser* giveParser();
    Writer* giveLexWriter();
    Writer* giveParseWriter();

    private:
    ScannerType type;
};

class LPG {
    public:
    LPG(ScannerType type);
    void generateParser(std::string lang_file);

    private:
    Parser *parser;
    Writer *lex_writer, *parse_writer;
};
