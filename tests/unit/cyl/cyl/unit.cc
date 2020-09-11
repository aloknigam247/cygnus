#include "cyl.h"
#include "cytest.h"

void CylTest() {
    Cyl cyl;
    cyl.readCyl("test.cyl");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(CylTest);
    testcase.run();
    return 0;
}
