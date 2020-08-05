#include "parser.h"
#include "cytest.h"
#include <cassert>

void testDigest() {
    Digest d;
    int i = 10;

    d.set_data((void*)&i);
    assert(*((int*)d.get_data()) == i);
}

int main() {
    cytest::Testcase testcase;
    testcase.add(testDigest);
    testcase.run();
    return 0;
}
