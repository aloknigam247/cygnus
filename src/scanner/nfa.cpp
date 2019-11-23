#include "nfa.h"

#include <cstdlib>
#include <fstream>

#include "log.h"

int NFA::state_id=1;

void NFA::addPattern(std::string patt) {
    m_patt_list.push_back(patt);
}

void NFA::compile() {
    for(auto patt: m_patt_list) {
        Log::d(patt);
        State* cur = &m_state;
        for(auto c: patt) {
            Log::d(c);
            cur = move(cur, c);
        }
        cur->is_final = true;
    }
}

void NFA::execute() {
}

void NFA::printStates(State& st) {
    const State* cur = &st;
    for(auto p: cur->next) {
        std::cout << 'q' << cur->id  << "--" << p.sym << "-->";
        printStates(*p.link);
    }
    if(cur->next.empty())
        std::cout << 'q' << cur->id << '\n';
}

void NFA::printDot() {
    std::ofstream dotfile("dotfile");
    dotfile << 
R"(digraph nfa {
    rankdir=LR;
)";
    traverse(m_state, dotfile);
    dotfile << "}\n";
    dotfile.close();

    std::system("dot -Tpng dotfile > t.png");
}

void NFA::traverse(State& st, std::ofstream& out) {
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

State* NFA::move(State* from, char sym) {
    State* new_state = new State(state_id++);
    from->next.push_back(State::pair(sym, new_state));
    return new_state;
}
