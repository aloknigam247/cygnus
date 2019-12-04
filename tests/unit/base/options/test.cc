#include "options.h"

#include "cytest.h"

void helpOption() {
    Options opt;
    const char* arg[] = {"cygnus", "-h"};
    opt.parse(2, arg);
}

void allOptionsType() {
    Options opt;
    opt.addOption("-b", Option::BOOL, "bool option");
    opt.addOption("-c", Option::CHAR, "bool option");
    opt.addOption("-i", Option::INT, "bool option");
    opt.addOption("-s", Option::STRING, "bool option");

    const char* arg0[] = {"cygnus"};
    opt.parse(1, arg0);
    const char* arg1[] = {"cygnus", "-b", "-c", "d", "-i","77", "-s", "string", "positional"};
    opt.parse(9, arg1);
    const char* arg2[] = {"cygnus", "-c", "-i", "-s"};
    opt.parse(4, arg2);
    const char* arg3[] = {"cygnus", "-c", "ac", "-i", "cd", "-u"};
    opt.parse(6, arg3);
    const char* arg4[] = {"cygnus", "-i", "999999999999999"};
    opt.parse(3, arg4);
}

int main() {
    cytest::Testcase testcase;
    testcase.add(helpOption);
    testcase.add(allOptionsType);
    testcase.run();
    return 0;
}
