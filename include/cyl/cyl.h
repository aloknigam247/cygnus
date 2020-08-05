#ifdef EXTENDED_FEATURE
#include "parser.h"
#include "writer.h"
#include "status.h"

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

class Cyl {
    public:
    Cyl(ScannerType type);
    Status generateParser(std::string lang_file);

    private:
    Parser *parser;
    Writer *lex_writer, *parse_writer;
};
#endif
