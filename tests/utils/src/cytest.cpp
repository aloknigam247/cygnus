#include "cytest.h"
#include <iostream>

namespace cytest {
void Testcase::add(caseType p) {
    case_list.push_back(p);
}

int Testcase::run() {
    std::cout << "Number of cases: " << case_list.size() << '\n';
    int i=1;
    for (auto case_p: case_list) {
        std::cout << "CASE " << i << '\n';
        case_p();
        i++;
    }
}
}
