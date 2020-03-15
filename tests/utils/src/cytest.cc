#include <iostream>
#include <stdexcept>

#include "cytest.h"

namespace cytest {
Session* Session::s = nullptr;

Session& Session::get() {
    if(!s)
        s = new Session;

    return *s;
}

void Testcase::add(caseType p) {
    Case c;
    c.case_ptr = p;
    for(int i=0; i<NumProperty; ++i)
        c.property[i] = property[i];
    case_list.push_back(c);
}

void Testcase::run() {
    Session &s = Session::get();
    std::cout << "Number of cases: " << case_list.size() << '\n';
    int i=1;
    for(auto case_obj: case_list) {
        std::cout << "CASE " << i << '\n';
        s.set_property_ptr(case_obj.property);
        case_obj.case_ptr();
        i++;
    }
    s.set_property_ptr(nullptr);
}

void Testcase::simulation_set(SimulateProperty prop) {
    property[prop] = true;
}

void Testcase::simulation_reset(SimulateProperty prop) {
    property[prop] = false;
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
