#include "cycase.h"
#include <iostream>

void Test::print(std::string msg) {
    std::cout << msg << '\n';
}

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
