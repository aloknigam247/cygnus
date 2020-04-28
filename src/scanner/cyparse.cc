#include "scanner/cyparse.h"
#include "scanner/cylex.h"

void CyParse::parse(std::string file) {
    CyLex lex;
    lex.addPattern("int");
    lex.addPattern("char");
    lex.addPattern("float");
    lex.readFile(file.c_str());
    lex.analyse();
}
