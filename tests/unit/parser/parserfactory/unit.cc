#include "parserfactory.h"
#include "cytest.h"

extern "C" {
void* CylBisonEntry(const char *c) {
    return nullptr;
}
}

void getAll() {
    Parser *p;
    p = parserFactory(ParserType::Bison);
    p = parserFactory(ParserType::CyParser);
}

int main() {
    cytest::Testcase testcase;
    testcase.add(getAll);
    testcase.run();
    return 0;
}
