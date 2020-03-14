#include "clg.h"

extern "C" void callme(const char *file);

CLG::CLG(std::string file) {
    callme(file.c_str());
}
