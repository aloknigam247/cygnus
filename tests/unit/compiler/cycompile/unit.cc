#include "cytest.h"

#include "cycompile.h"

void init() {
    CyCompile comp("testfile");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(init);
    testcase.run();
}
