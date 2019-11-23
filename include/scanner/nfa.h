#ifndef NFA_H
#define NFA_H

#include <string>
#include <vector>

struct State {
    struct pair {
        char sym;
        State* link;
        pair() {}
        pair(char s, State* l): sym(s), link(l) {}
    };
    bool is_final;
    int id;
    std::vector<pair> next;
    State(int id): is_final(false), id(id), next(0) {}
};

class NFA {
    public:
    NFA(): m_patt_list(), m_state(0) {}
    void addPattern(std::string patt);
    void compile();
    void execute();
    void printStates(State& st);
    void printDot();
    State& get_state() { return m_state; }

    private:
    static int state_id;
    State* move(State* from, char sym);
    std::vector<std::string> m_patt_list;
    State m_state;
    void traverse(State& st, std::ofstream& out);
};

#endif
