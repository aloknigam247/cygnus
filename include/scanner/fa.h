#ifndef FA_H
#define FA_H

#include <fstream>
#include <vector>

class FA {
    public:
    void printTPaths();
    void printTGraph(const char* file_stem = "fa");

    protected:
    struct State {
        struct Pair {
            char sym;
            State* link;
            Pair(char s, State* l): sym(s), link(l) {}
        };
        bool is_final;
        int id;
        std::vector<Pair> next;
        State(int p_id): is_final(false), id(p_id), next() {}
    };

    FA(): m_state(0) {}
    State* addTransition(State* from, char sym);
    State m_state;
    void traversePath(State& st);
    void traverseGraph(State& st, std::ofstream& out);
    int genStateId();
};

#endif
