#include "cyl.h"
#include "cytest.h"
#include <cassert>

/*
extern "C" {
void* CylBisonEntry(const char *c) {
    return nullptr;
}
}
*/

void ScannerFactoryTest() {
    ScannerFactory cygnus_factory(Cygnus);
    assert(cygnus_factory.giveParser() != nullptr);
    assert(cygnus_factory.giveLexWriter() != nullptr);
    assert(cygnus_factory.giveParseWriter() != nullptr);

    ScannerFactory gnu_factory(GNU);
    assert(gnu_factory.giveParser() != nullptr);
    assert(gnu_factory.giveLexWriter() != nullptr);
    assert(gnu_factory.giveParseWriter() != nullptr);
}

void CylCygnusTest() {
    Cyl cyl(Cygnus);
}

void CylGNUTest() {
    Cyl cyl(GNU);
    cyl.generateParser("file");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(ScannerFactoryTest);
    testcase.add(CylCygnusTest);
    testcase.add(CylGNUTest);
    testcase.run();
    return 0;
}
