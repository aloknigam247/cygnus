#include "cyparser.h"
#include "cytest.h"
#include "cyl.h"

void parse() {
    Cyl cyl;
    cyl.readCyl("test.cyl");

    CyParser parser;
    parser.setLangBlock(cyl.getLangBlock()[0]);

    CyDigest *d = parser.parse("test.c");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(parse);
    testcase.run();
    return 0;
}
