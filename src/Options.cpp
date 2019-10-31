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

#include "Options.h"

#include <string.h>

#include "Log.h"

Options::Options(): option_list(), pos_args() {
    addOption("-h", Option::BOOL, "print help message");
}

void Options::addOption(const std::string pi_option_name,
                        Option::Type pi_type,
                        const std::string pi_help) {
    option_list.insert(new Option(pi_option_name, pi_type, pi_help));
}

bool Options::parse(const int pi_argc, const char* pi_argv[]) {
    if(pi_argc == 1)
        return false;

    bool result = true;
    for(int i=1; i<pi_argc; ++i) {
        const char* opt = pi_argv[i];
        if(opt[0] == '-') {
            cystructs::Tree<Option*>::iterator iter;
            iter = option_list.search(opt);
            if(iter != option_list.end()) {
                switch(iter->get_type()){
                    case Option::BOOL:
                        iter->set_value(true);
                        break;
                    case Option::CHAR:
                        if(i+1 < pi_argc && strlen(pi_argv[i+1]) == 1)
                            iter->set_value(*pi_argv[++i]);
                        else {
                            Log::e("option ", opt, " needs value character value.");
                            result = false;
                        }
                        break;
                    case Option::INT:
                        if(i+1 < pi_argc && pi_argv[i+1][0] != '-')
                            try{
                                iter->set_value(std::stoi(pi_argv[++i]));
                            }
                            catch (const std::invalid_argument& e) {
                                Log::e(pi_argv[i], " is not a valid integer.");
                                result = false;
                            }
                            catch (const std::out_of_range& e) {
                                Log::e(pi_argv[i], " is out of range.");
                                result = false;
                            }
                        else {
                            Log::e("option ", opt, " needs value integer value.");
                            result = false;
                        }
                        break;
                    case Option::STRING:
                        if(i+1 < pi_argc && pi_argv[i+1][0] != '-')
                            iter->set_value(pi_argv[++i]);
                        else {
                            Log::e("option ", opt, " needs value string value.");
                            result = false;
                        }
                        break;
                    default:
                        Log::e("Option not suppoted");
                }
            }
            else
                Log::w("ignoring unknown option ", opt);
        }
        else {
            pos_args.push_back(std::string(opt));
        }
    }
    cystructs::Tree<Option*>::iterator iter = option_list.search("-h");
    if(iter != option_list.end() && iter->get_bool_value()) {
        usage();
        result = false;
    }
    return result;
}

void Options::usage() const {
    cystructs::Tree<Option*>::iterator iter;
    std::cout << "usage: cygnus [options]\n";
    for(iter = option_list.begin(); iter != option_list.end(); ++iter) {
        Option* opt = *iter;
        std::cout << "    " <<opt->get_name() << ": " << opt->get_help() << '\n';
    }
}
