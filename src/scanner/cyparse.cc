#ifdef EXTENDED_FEATURE
#include "parser.h"
#include "cylex.h"

void CyParser::parse(std::string file) {
    CyLex lex;
    lex.addPattern("int");
    lex.addPattern("char");
    lex.addPattern("float");
    lex.readFile(file.c_str());
    lex.analyse();
}
#endif
