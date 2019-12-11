#include "fa.h"

#include "log.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

void FA::printTPaths() {
    traversePath(m_state);
}

void FA::printTGraph(const char* file_stem) {
    std::ofstream dotfile(file_stem);
    dotfile << 
R"(digraph fa {
    rankdir=LR;
)";
    traverseGraph(m_state, dotfile);
    dotfile << "}\n";
    dotfile.close();

    char* cmd = new char[(std::strlen(file_stem)*2+17)*sizeof(char)];
    std::strcpy(cmd, "dot -Tpng ");
    std::strcpy(cmd+10, file_stem);
    std::strcpy(cmd+10+std::strlen(file_stem), " > ");
    std::strcpy(cmd+10+std::strlen(file_stem)+3, file_stem);
    std::strcpy(cmd+10+std::strlen(file_stem)+3+std::strlen(file_stem), ".png");
    if(!std::system(cmd))
        Log::e("error: ", cmd);
    delete cmd;
}

void FA::traversePath(State& st) {
    const FA::State* cur = &st;
    for(auto p: cur->next) {
        if(cur->is_final)
            std::cout << "((q" << cur->id << "))--" << p.sym << "-->";
        else
            std::cout << "(q" << cur->id << ")--" << p.sym << "-->";
        traversePath(*p.link);
    }
    if(cur->next.empty()) {
        if(cur->is_final)
            std::cout << "((q" << cur->id << "))\n";
        else
            std::cout << "(q" << cur->id << ")\n";
    }
}

void FA::traverseGraph(State& st, std::ofstream& out) {
    for(auto p: st.next) {
        out << "    {";
        if(st.is_final)
            out << "node [shape=doublecircle] ";
        out << "q" << st.id  << "} -> {";
        if(p.link->is_final)
            out << "node [shape=doublecircle] ";
        out << "q" << p.link->id << "} [label=\"" << p.sym << "\"]\n";
        traverseGraph(*p.link, out);
    }
}

FA::State* FA::addTransition(State* from, char sym) {
    State* new_state = new State(genStateId());
    from->next.push_back(State::Pair(sym, new_state));
    return new_state;
}

int FA::genStateId() {
    static int state_id = 0;
    return ++state_id;
}
