#include <iostream>

#include "cytest.h"
#include "cyperf.h"
CyPerf global_perf(nullptr, nullptr);

namespace cytest {
void Testcase::add(caseType p) {
    Case c;
    c.case_ptr = p;
    case_list.push_back(c);
}

void Testcase::run() {
    int i=1;
    for(auto case_obj: case_list) {
        std::cout << "[CASE " << i << ']' << '\n';
        case_obj.case_ptr();
        std::cout << '\n';
        ++i;
    }
}
}

void* operator new(const std::size_t s) {
    void* p = std::malloc(s);

    if(p == nullptr)
        throw std::bad_alloc();

    return p;
}

void* operator new[](const std::size_t s) {
    void* p = std::malloc(s);

    if(p == nullptr)
        throw std::bad_alloc();

    return p;
}

void operator delete(void* ptr) {
    std::free(ptr);
}

void operator delete[](void* ptr) {
    std::free(ptr);
}
