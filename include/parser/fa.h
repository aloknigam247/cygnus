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

#ifdef EXTENDED_FEATURE

#ifndef SCANNER_FA_H
#define SCANNER_FA_H

#include <fstream>
#include <list>
#include <string>
#include <vector>

#include "log.h"

struct State {
    std::vector<int> sym[128];
    bool final_state;
    std::string tag;
};

struct Metrics {
    int max_len;
    int len[129];
    bool is_filled[129];
};

class StateTable {
    public:
    void addEntry(int from, char sym, int to);
    void print() const;
    void printDot(std::ofstream& file) const;
    void set_final(int i) { if(i>=row.size()) row.resize(i+1); row[i].final_state = true;}
    State* get_state(int i) { return &(row[i]); }
    size_t size() { return row.size(); }
    std::vector<State> row;

    private:
    Metrics met;
    Metrics calcMetrics() const;
};

class FA {
    public:
    void printTable() const;
    void printDot(const char* file_stem = "fa") const;
    StateTable& get_table() { return table; }
    StateTable table;

    protected:
    int addTransition(int from, char sym, int to=-1);
    int addTransition(const std::vector<int>& from, char sym, int to=-1);

    private:
    int state_id = 0;
};

#endif

#endif
