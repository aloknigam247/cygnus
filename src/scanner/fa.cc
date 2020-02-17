/************************************************************************************
 * MIT License                                                                      *
 *                                                                                  *
 * Copyright (c) 2019 Alok Nigam                                                    *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person obtaining a copy     *
 * of this software and associated documentation files (the "Software"), to deal    *
 * in the Software without restriction, including without limitation the rights     *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 * copies of the Software, and to permit persons to whom the Software is            *
 * furnished to do so, subject to the following conditions:                         *
 *                                                                                  *
 * The above copyright notice and this permission notice shall be included in all   *
 * copies or substantial portions of the Software.                                  *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    *
 * SOFTWARE.                                                                        *
 ************************************************************************************/

#include "fa.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>

void StateTable::addEntry(int from, char sym, int to) {
    if(from >= row.size())
        row.resize(from+1); // +1 may be wrong
    if(to >= row.size())
        row.resize(to+1);
    row[from].sym[sym].push_back(to);
    if(row[from].tag.empty()) {
        row[from].tag += 'q';
        row[from].tag += std::to_string(from);
    }
    if(row[to].tag.empty()) {
        row[to].tag += 'q';
        row[to].tag += std::to_string(to);
    }
}

Metrics StateTable::calcMetrics() const{
    Metrics m;
    int max_len, len, s;
    m.len[0] = 6;
    for(auto &a: m.is_filled)
        a = false;

    for(auto r: row) {
        if(r.tag.size() > m.len[0])
            m.len[0] = r.tag.size();
        len = m.len[0];
        for(int i=0; i<128; ++i) {
            s=1;
            if(!r.sym[i].size())
                s += 1;
            else {
                m.is_filled[i] = true;
                for(auto a: r.sym[i]) {
                    s += std::to_string(a).size();
                }
                s += r.sym[i].size()-1;
            }
            if(s>m.len[i])
                m.len[i] = s;
            if(m.is_filled[i]) {
                len += m.len[i];
            }
        }
        len += 1;
        if(len > max_len) max_len = len;
    }

    m.max_len = max_len;

    return m;
}


template<typename T>
void col(Metrics& m, int i, T t) {
    std::cout << '|' << std::setw(m.len[i]-1) << t << std::setw(0);
}

void line(int len) {
    for(int i=0; i<len; ++i)
        std::cout << '-';
    std::cout << '\n';
}

void StateTable::print() const {
    Metrics m = calcMetrics();

    line(m.max_len);
    col(m, 0, "State");
    for(int i=32; i<128; ++i) {
        if(!m.is_filled[i])
            continue;
        switch(i) {
            case 92:
            case 127:
                   col(m, i, ' ');
                   break;
            default:
                   col(m, i, char(i));
        }
    }
    std::cout << '|';
    std::cout << '\n';
    line(m.max_len);
    for(auto r: row) {
        if(r.finalState) {
            std::string s;
            s = '(';
            s+= r.tag;
            s += ')';
            col(m, 0, s);
        }
        else
            col(m,0,r.tag);
        for(int i=32; i<128; ++i) {
            if(!m.is_filled[i])
                continue;
            if(!r.sym[i].size()) {
                col(m, i, ' ');
            }
            else {
                std::string st;
                for(auto a: r.sym[i]) {
                    st += std::to_string(a);
                    st += ',';
                }
                st.resize(st.size()-1);
                col(m,i,st);
            }
        }
        std::cout << "|\n";
        line(m.max_len);
    }
}

void StateTable::printDot(std::ofstream& file) const {
    /*file << "digraph fa {\n"
        << "    rankdir=LR;\n";
    for(int r=0; r<100; ++r) {
        for(int c=0; c<100; ++c) {
            if(!state_entry[r][c].empty())
                file << "    {";
                if(is_final[r])
                    file << "node [shape=doublecircle] ";
                file << entry->tag << "} -> {";
                if(is_final[c])
                    file << "node [shape=doublecircle] ";
                file << state_entry[transition.state_id]->tag << "} [label=\"" << transition.sym << "\"]\n";
            }
        }
    }
    file << "}\n";*/
}


void FA::printTable() const {
    table.print();
}

void FA::printDot(const char* file_stem) const {
    /*std::ofstream dotfile(file_stem);
    table.printDot(dotfile);
    dotfile.close();

    std::string command;

    command = "dot -Tpng ";
    command += file_stem;
    command += " > ";
    command += file_stem;
    command += ".png";
    std::system(command.c_str());*/
}

int FA::addTransition(int from, char sym, int to) {
    if(to == -1)
        to = ++state_id;
    table.addEntry(from, sym, to);
    return to;
}

int FA::addTransition(const std::vector<int>& from, char sym, int to) {
    if(to == -1)
        to = ++state_id;
    for(auto f: from)
        table.addEntry(f, sym, to);
    return to;
}
