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
        std::vector<Pair> next;
        int id;
        bool is_final;
        State(int id): next(), id(id), is_final(false) {}
    };

    FA(): m_state(0) {}
    static int state_id;
    State* addTransition(State* from, char sym, State* to=nullptr);
    std::vector<State*> addTransition(std::vector<State*> from, char sym, State* to=nullptr);
    State m_state;
    void traversePath(State& st, std::vector<bool>& visited);
    void traverseGraph(State& st, std::ofstream& out, std::vector<bool>& visited);
};

#endif
