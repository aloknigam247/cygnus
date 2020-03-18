#include "clg.h"

extern "C" void callme(const char *file);

int CLG::parse(std::string file) {
    callme(file.c_str());
    return 0;
}
