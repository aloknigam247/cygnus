#include "cytest.h"

#include "compiler/cycompile.h"

void init() {
    CyCompile comp("testfile");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(init);
    testcase.run();
}
