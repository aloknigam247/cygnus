#ifndef CYTEST_H
#define CYTEST_H

#include <iostream>
#include <string>
#include <vector>

namespace cytest {
class Log {
    public:
    template <typename... Args>
    static void d(const Args... args) { std::cout << "[DEBUG] "; display(args...); }
    template <typename... Args>
    static void e(const Args... args) { std::cout << "[ERROR] "; display(args...); }
    template <typename... Args>
    static void i(const Args... args) { std::cout << "[INFO] "; display(args...); }
    template <typename... Args>
    static void w(const Args... args) { std::cout << "[WARN] "; display(args...); }

    private:
    template <typename T, typename... Args>
    static void display(T first, Args... args) {
        std::cout << first;
        display(args...);
    }

    static void display() { std::cout << std::endl; }
};

typedef void (*caseType)();

enum SimulateProperty {
    NumProperty
};

class Session {
    public:
    static Session& get();
    void set_property_ptr(bool *p) { property = p; }
    bool get_property(SimulateProperty prop) { return property == nullptr ? false : property[prop]; }

    private:
    Session() : property(nullptr) {}
    static Session* s;
    bool *property;
};

struct Case {
    caseType case_ptr;
    bool property[NumProperty];
};

class Testcase {
    public:
    void add(caseType p);
    void run();
    void simulation_set(SimulateProperty prop);
    void simulation_reset(SimulateProperty prop);

    private:
    std::vector<Case> case_list;
    bool property[NumProperty];
};
}

#endif
