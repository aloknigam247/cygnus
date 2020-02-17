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

#include "nfa.h"

#include "log.h"

void NFA::addPattern(const char* patt) {
    m_patt_list.push_back(patt);
}

void NFA::build() {
    for(auto patt: m_patt_list) {
        std::vector<int> curr;
        std::vector<int> prev;
        curr.push_back(0);
        for(int i=0; patt[i]!='\0'; ++i) {
            switch(patt[i]) {
                case '+':
                    addTransition(curr.front(), patt[i-1], curr.front());
                    break;
                case '?':
                    curr.push_back(prev.front());
                    break;
                case '*':
                    addTransition(curr.front(), patt[i-1], curr.front());
                    curr.push_back(prev.front());
                    break;
                default:
                    prev = move(curr);
                    curr.clear();
                    curr.push_back(addTransition(prev, patt[i]));
            }
        }
        for(auto curr_st: curr)
            get_table().set_final(curr_st);
    }
}
