/************************************************************************************
 * MIT License                                                                      *
 *                                                                                  *
 * Copyright (c) 2020 Alok Nigam                                                    *
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

#include "options.h"

#include <cstring>
#include <exception>

#include "log.h"

Options::Options(): m_option_list(), m_pos_args() {
    addOption("-h", Option::BOOL, "print help message");
}

Options::~Options() {
    try {
        for(auto opt : m_option_list)
            delete opt;
    }
    catch(std::exception& e) {
        Log::e(e.what());
    }
}

void Options::addOption(const std::string& option_name,
                        Option::Type type,
                        const std::string& help) {
    m_option_list.insert(new Option(option_name, type, help));
}

Status Options::parse(const int argc, const char* argv[]) {
    if(argc == 1)
        return Status::SUCCESS;

    Status status = Status::SUCCESS;
    for(int i=1; i<argc; ++i) {
        const char* opt = argv[i];
        if(opt[0] == '-') {
            cystructs::Tree<Option*>::iterator iter;
            iter = m_option_list.search(opt);
            if(iter != m_option_list.end()) {
                switch(iter->get_type()) {
                    case Option::BOOL:
                        iter->set_value(true);
                        break;
#ifdef EXTENDED_FEATURE
                    case Option::CHAR:
                        if(i+1 < argc && strlen(argv[i+1]) == 1)
                            iter->set_value(*argv[++i]);
                        else {
                            Log::e("option ", opt, " needs character value.");
                            status = Status::PARAM_TYPE_MISMATCH;
                        }
                        break;
                    case Option::INT:
                        if(i+1 < argc && argv[i+1][0] != '-')
                            try {
                                iter->set_value(std::stoi(argv[++i]));
                            }
                            catch (const std::invalid_argument& e) {
                                Log::e(argv[i], " is not a valid integer.");
                                status = Status::PARAM_TYPE_MISMATCH;
                            }
                            catch (const std::out_of_range& e) {
                                Log::e(argv[i], " is out of range.");
                                status = Status::PARAM_TYPE_MISMATCH;
                            }
                        else {
                            Log::e("option ", opt, " needs integer value.");
                            status = Status::PARAM_TYPE_MISMATCH;
                        }
                        break;
                    case Option::STRING:
                        if(i+1 < argc && argv[i+1][0] != '-')
                            iter->set_value(argv[++i]);
                        else {
                            Log::e("option ", opt, " needs string value.");
                            status = Status::PARAM_TYPE_MISMATCH;
                        }
                        break;
                    default:
                        Log::e("Option not suppoted");
#endif
                }
            }
            else {
                Log::e("unknown option ", opt);
                status = Status::PARAM_UNKNOWN;
            }
        }
        else {
            m_pos_args.emplace_back(opt);
        }
    }
    cystructs::Tree<Option*>::iterator iter = m_option_list.search("-h");
    if(iter != m_option_list.end() && iter->get_bool_value() && status == Status::SUCCESS) {
        usage();
    }
    return status;
}

bool Options::isSet(const std::string& opt_name) {
    cystructs::Tree<Option*>::iterator iter = m_option_list.search(opt_name);
    return (iter != m_option_list.end() && iter->isSet());
}

#ifdef EXTENDED_FEATURE
Option::Value Options::get_value(const std::string& opt_name) {
    cystructs::Tree<Option*>::iterator iter = m_option_list.search(opt_name);
    if(iter != m_option_list.end()) {
        switch(iter->get_type()) {
            case Option::BOOL:
                return Option::Value(iter->get_bool_value());
            case Option::CHAR:
                return Option::Value(iter->get_char_value());
            case Option::INT:
                return Option::Value(iter->get_int_value());
            case Option::STRING:
                return Option::Value(iter->get_string_value());
            default:
                return {};
        }
    }
    return {};
}
#endif

void Options::usage() const {
    cystructs::Tree<Option*>::iterator iter;
    std::cout << "usage: cygnus [options]\n";
    for(iter = m_option_list.begin(); iter != m_option_list.end(); ++iter) {
        Option* opt = *iter;
        std::cout << "    " <<opt->get_name() << ": " << opt->get_help() << '\n';
    }
}
