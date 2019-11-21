#ifndef NFA_H
#define NFA_H

#include <string>
#include <vector>

struct State {
    bool is_final;
    char input_sym;
    int id;
    State* next;
    State(int id): is_final(false), input_sym(0), id(id), next(nullptr) {}
};

class NFA {
    public:
    NFA(): m_patt_list(), m_state(0) {}
    void addPattern(std::string patt);
    void compile();
    void execute();
    void printStates();
    void printDot();

    private:
    State* move(State* from, char sym);
    std::vector<std::string> m_patt_list;
    State m_state;
};

#endif
