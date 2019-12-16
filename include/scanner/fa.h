#ifndef FA_H
#define FA_H

#include <fstream>
#include <list>
#include <string>
#include <vector>

#include "log.h"

struct StateEntry {
    struct Transition {
        char sym;
        int state_id;
    };

    std::string tag;
    bool is_final;
    std::list<Transition> transition_list;
    StateEntry(): tag("q"), is_final(false), transition_list(0) {}
};

class StateTable {
    public:
    StateTable(): state_entry(100, nullptr) {}
    void addEntry(int from, char sym, int to);
    void print() const;
    void printDot(std::ofstream& file) const;
    void set_final(int i) { state_entry[i]->is_final = true; }

    private:
    std::vector<StateEntry*> state_entry;
};

class FA {
    public:
    void printTable() const;
    void printGraph(const char* file_stem = "fa") const;

    protected:
    StateTable table;
    FA(): state_id(0) {}
    int addTransition(int from, char sym, int to=-1);
    int addTransition(std::vector<int> from, char sym, int to=-1);

    private:
    int state_id;
};

#endif
