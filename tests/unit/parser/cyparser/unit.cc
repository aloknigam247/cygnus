#include "cyparser.h"
#include "cytest.h"

#include <cassert>

void parse() {
    CyParser p;
    Digest *d = p.parse("test.cyl");
    assert(d == nullptr);
}

int main() {
    cytest::Testcase testcase;
    testcase.add(parse);
    testcase.run();
    return 0;
}
