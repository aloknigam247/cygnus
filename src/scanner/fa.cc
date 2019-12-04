#include "fa.h"

#include <cstdlib>

#include "log.h"

void FA::printTPaths(State& st) {
    const FA::State* cur = &st;
    for(auto p: cur->next) {
        std::cout << 'q' << cur->id  << "--" << p.sym << "-->";
        printTPaths(*p.link);
    }
    if(cur->next.empty())
        std::cout << 'q' << cur->id << '\n';
}

void FA::printTGraph() {
    std::ofstream dotfile("dotfile");
    dotfile << 
R"(digraph fa {
    rankdir=LR;
)";
    traverse(m_state, dotfile);
    dotfile << "}\n";
    dotfile.close();

    std::system("dot -Tpng dotfile > t.png");
}

void FA::traverse(State& st, std::ofstream& out) {
    for(auto p: st.next) {
        out << "    "<< 'q' << st.id  << " -> ";
        if(p.link->is_final)
            out << "{node [shape=doublecircle] q" << p.link->id << " }";
        else
            out << 'q' << p.link->id;
        out << " [label=\"" << p.sym << "\"]\n";
        traverse(*p.link, out);
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
