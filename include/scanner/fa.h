#ifndef FA_H
#define FA_H

#include <fstream>
#include <vector>

class FA {
    public:
    struct State {
        struct Pair {
            char sym;
            State* link;
            Pair(char s, State* l): sym(s), link(l) {}
        };
        bool is_final;
        int id;
        std::vector<Pair> next;
        State(int id): is_final(false), id(id), next() {}
    };

    void printTPaths(State& st);
    void printTGraph();
    State& get_state() { return m_state; }

    protected:
    FA(): m_state(0) {}
    State* addTransition(State* from, char sym);
    State m_state;
    void traverse(State& st, std::ofstream& out);
    int genStateId();
};

#endif
