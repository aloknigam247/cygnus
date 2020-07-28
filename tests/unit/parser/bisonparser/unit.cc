#include "bisonparser.h"
#include "cytest.h"

#include <cassert>

extern "C" {
void* CylBisonEntry(const char *c) {
    return nullptr;
}
}

void parse() {
    BisonParser p;
    Digest *d = p.parse("test.cyl");
    assert(d != nullptr);
    assert(d->get_data() == nullptr);
}

int main() {
    cytest::Testcase testcase;
    testcase.add(parse);
    testcase.run();
    return 0;
}
