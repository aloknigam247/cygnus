#include "options.h"

#include "cytest.h"

void helpOption() {
    Options opt;
    const char* arg[] = {"cygnus", "-h"};
    opt.parse(2, arg);
}

void allOptionsType() {
    Options opt;
    opt.addOption("-b", Option::BOOL, "testing BOOL option");
    opt.addOption("-c", Option::CHAR, "testing CHAR option");
    opt.addOption("-i", Option::INT, "testing INT option");
    opt.addOption("-s", Option::STRING, "testing STRING option");

    const char* arg0[] = {"cygnus"};
    opt.parse(1, arg0);
    const char* arg1[] = {"cygnus", "-b", "-c", "d", "-i","77", "-s", "string", "positional"};  /* expected arguments */
    opt.parse(9, arg1);
    const char* arg2[] = {"cygnus", "-c", "-i", "-s"};
    opt.parse(4, arg2);
    const char* arg3[] = {"cygnus", "-c", "ac", "-i", "cd", "-u"};  /* invalid arguments */
    opt.parse(6, arg3);
    const char* arg4[] = {"cygnus", "-i", "999999999999999"};   /* out of range */
    opt.parse(3, arg4);
}

void reParse() {
    Options opt;
    opt.addOption("-a", Option::INT, "testing INT option");
    opt.addOption("-b", Option::INT, "testing INT option");

    const char* arg0[] = {"cygnus", "-a", "123"};
    opt.parse(3, arg0);
    cytest::Log::i("Options value:");
    if(opt.isSet("-a"))
        cytest::Log::i(static_cast<int>(opt.get_value("-a")));
    else
        cytest::Log::i("Not set");
    if(opt.isSet("-b"))
        cytest::Log::i(static_cast<int>(opt.get_value("-b")));
    else
        cytest::Log::i("Not set");

    /* previous options should be cleared */
    const char* arg1[]= {"cygnus", "-b", "456"};
    opt.parse(3, arg1);
    cytest::Log::i("Options value:");
    if(opt.isSet("-a"))
        cytest::Log::i(static_cast<int>(opt.get_value("-a")));
    else
        cytest::Log::i("Not set");
    if(opt.isSet("-b"))
        cytest::Log::i(static_cast<int>(opt.get_value("-b")));
    else
        cytest::Log::i("Not set");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(helpOption);
    testcase.add(allOptionsType);
    testcase.add(reParse);
    testcase.run();
    return 0;
}
