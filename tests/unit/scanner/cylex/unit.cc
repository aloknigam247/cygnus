#include "scanner/cylex.h"

#include "cytest.h"

void analyseFile() {
    CyLex lex;

    lex.addPattern("int");
    lex.addPattern("float");
    lex.readFile("text");
    lex.analyse();
}

int main() {
    cytest::Testcase t;
    t.add(analyseFile);
    t.run();
}
