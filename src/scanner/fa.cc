#include "fa.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

int FA::state_id = 0;

void FA::printTPaths() {
    std::vector<bool> visited(state_id);
    traversePath(m_state, visited);
}

void FA::printTGraph(const char* file_stem) {
    std::ofstream dotfile(file_stem);
    dotfile << 
R"(digraph fa {
    rankdir=LR;
)";
    std::vector<bool> visited(state_id);
    traverseGraph(m_state, dotfile, visited);
    dotfile << "}\n";
    dotfile.close();

    char command[std::strlen(file_stem)*2+17];
    std::strcpy(command, "dot -Tpng ");
    std::strcpy(command+10, file_stem);
    std::strcpy(command+10+std::strlen(file_stem), " > ");
    std::strcpy(command+10+std::strlen(file_stem)+3, file_stem);
    std::strcpy(command+10+std::strlen(file_stem)+3+std::strlen(file_stem), ".png");
    std::system(command);
}

void FA::traversePath(State& st, std::vector<bool>& visited) {
    if(visited[st.id])
        return;
    visited[st.id] = true;
    const FA::State* cur = &st;
    for(auto p: cur->next) {
        if(cur->is_final)
            std::cout << "((q" << cur->id << "))--" << p.sym << "-->";
        else
            std::cout << "(q" << cur->id << ")--" << p.sym << "-->";
        if(p.link->id > cur->id)
            traversePath(*p.link, visited);
    }
    if(cur->next.empty())
        if(cur->is_final)
            std::cout << "((q" << cur->id << "))\n";
        else
            std::cout << "(q" << cur->id << ")\n";
}

void FA::traverseGraph(State& st, std::ofstream& out, std::vector<bool>& visited) {
    if(visited[st.id])
        return;
    visited[st.id] = true;
    for(auto p: st.next) {
        out << "    {";
        if(st.is_final)
            out << "node [shape=doublecircle] ";
        out << "q" << st.id  << "} -> {";
        if(p.link->is_final)
            out << "node [shape=doublecircle] ";
        out << "q" << p.link->id << "} [label=\"" << p.sym << "\"]\n";
        if(p.link->id > st.id)
            traverseGraph(*p.link, out, visited);
    }
}

FA::State* FA::addTransition(State* from, char sym, State* to) {
    State* new_state = to ? to : new State(++state_id);
    from->next.push_back(State::Pair(sym, new_state));
    return new_state;
}

std::vector<FA::State*> FA::addTransition(std::vector<State*> from, char sym, State* to) {
    State* new_state = to ? to : new State(++state_id);
    for(auto from_st: from) {
        from_st->next.push_back(State::Pair(sym, new_state));
    }
    return std::vector<State*>(1, new_state);
}
