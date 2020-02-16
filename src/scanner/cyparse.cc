#include "cyparse.h"

void CyParse::parse(std::string file) {
    CyLex lex;
    addPattern("int");
    lex.readFile(file.c_str());
}
