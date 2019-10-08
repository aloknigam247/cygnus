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

#ifndef _OPTIONS_H
#define _OPTIONS_H

#include <string>
#include <vector>

#include "cystructs.h"

class Option {
    union Value;

    public:
    enum Type {
        BOOL,
        CHAR,
        INT,
        STRING
    };

    Option(const std::string pi_name, Type pi_type, std::string pi_help) :
        name(pi_name), type(pi_type), help(pi_help), value(0) {}
    
    std::string get_help() const { return help;  }
    std::string get_name() const { return name;  }
    Type get_type() const        { return type;  }
    Value get_value() const      { return value; }
    
    void set_value(const bool  pi_value) { value.b = pi_value; }
    void set_value(const char  pi_value) { value.c = pi_value; }
    void set_value(const int   pi_value) { value.i = pi_value; }
    void set_value(const char* pi_value) { value.s = pi_value; }
    
    bool operator>(const Option& pi_opt) { return name > pi_opt.name; }
    bool operator>(const char* pi_opt)   { return name > pi_opt;      }
    bool operator==(const char* pi_opt)  { return name == pi_opt;     }
    
    private:
    union Value {
        bool b;
        char c;
        int i;
        const char* s;
        Value(const int pi_i) : s(nullptr) {}
    };

    const std::string name, help;
    const Type type;
    Value value;
};

class Options {
    public:
    Options();
    void addOption(const std::string pi_option_name, Option::Type, const std::string pi_help);
    bool parse(const int pi_argc, const char* argv[]);
    const std::vector<std::string>& get_positional() const { return pos_args; }
    void usage() const;

    private:
    cystructs::Tree<Option*> option_list;
    std::vector<std::string> pos_args;
};

#endif
