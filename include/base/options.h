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

/**
 * @file Options.h
 * @brief Command line parser
 *
 * Parses command line option and perform error handling for command line
 *
 * @author Alok Nigam
 */

#ifndef BASE_OPTIONS_H
#define BASE_OPTIONS_H

#include <string>
#include <vector>

#include "cystructs.h"

/**
 * @class Option
 * @brief Single option entity
 *
 * Represents single option and is supposed to handle one option at a time
 */
class Option {
    public:
    union Value;

    /**
     * @enum Type
     * Option types
     * Valid types are:
     * * BOOL
     * * CHAR
     * * INT
     * * STRING
     */
    enum Type {
        BOOL,
        CHAR,
        INT,
        STRING
    };

    /**
     * Paranetrised constructor
     *
     * @param[in] name name of option
     * @param[in] type type of option
     * @param[in] help help of option
     */
    Option(const std::string& name, Type type, const std::string& help) :
        is_set(false), m_name(name), m_help(help), m_type(type), m_value() {}

    /**
     * Tells if options is set
     *
     * @return true if option set
     */
    bool isSet() { return is_set; }

    /**
     * Get help
     *
     * @returns help
     */
    std::string get_help() const { return m_help; }

    /**
     * Get option name
     *
     * @returns option name
     */
    std::string get_name() const { return m_name; }

    /**
     * Get option type
     *
     * @returns option type
     */
    Type get_type() const { return m_type; }

    /**
     * Get bool value
     *
     * @returns bool value
     */
    bool get_bool_value() const { return m_value.b; }

#ifdef EXTENDED_FEATURE
    /**
     * Get char value
     *
     * @returns char value
     */
    char get_char_value() const { return m_value.c; }

    /**
     * Get int value
     *
     * @returns int value
     */
    int get_int_value() const { return m_value.i; }
#endif

    /**
     * Get string value
     *
     * @returns string value
     */
    const char* get_string_value() const { return m_value.s; }

    /**
     * Set bool value
     *
     * @param[in] value bool value
     */
    void set_value(const bool value) { is_set = true; m_value.b = value; }

#ifdef EXTENDED_FEATURE
    /**
     * Set char value
     *
     * @param[in] value char value
     */
    void set_value(const char value) { is_set = true; m_value.c = value; }

    /**
     * Set int value
     *
     * @param[in] value int value
     */
    void set_value(const int value) { is_set = true; m_value.i = value; }
#endif

    /**
     * Set string value
     *
     * @param[in] value string value
     */
    void set_value(const char* value) { is_set = true; m_value.s = value; }

    /**
     * Operator>
     *
     * @param[in] opt Option to compare
     * @returns true if left Option is greater than right Option are equal
     */
    bool operator>(const Option& opt) { return m_name > opt.m_name; }

    /**
     * Operator>
     *
     * @param[in] opt string to compare
     * @returns true if Option name is greater than string on the right
     */
    bool operator>(const std::string& opt) { return m_name > opt; }

    /**
     * Operator==
     *
     * @param[in] opt Option to compare
     * @returns true if both options are equal
     */
    bool operator==(const std::string& opt) { return m_name == opt; }

    /**
     * @union Value
     *
     * Stores value of different types in a single union
     */
    union Value {
        bool b; /* TODO: obsolete */
        char c;
        int i;
        const char* s;

        /**
         * Default constructor
         */
        Value() : s(nullptr) {}
#ifdef EXTENDED_FEATURE
        explicit Value(bool m_b) : b(m_b) {}
        explicit Value(char m_c) : c(m_c) {}
        explicit Value(int m_i) : i(m_i) {}
#endif
        explicit Value(const char* m_s) : s(m_s) {}

        explicit operator bool() { return b; }
        explicit operator char() { return c; }
        explicit operator int() { return i; }
        explicit operator const char*() { return s; }
    };

    private:
    bool is_set;
    const std::string m_name, m_help;
    const Type m_type;
    Value m_value;
};

/**
 * @class Options
 * @brief Option parser
 *
 * Collection of Option and process all quesries and error handling on command line parsing
 */
class Options {
    public:
    /**
     * Default constructor
     */
    Options();

    /**
     * Destructor
     */
    ~Options();

    /**
     * Adds Option to option list
     *
     * @param[in] option_name name of option
     * @param[in] type type of option
     * @param[in] help option help
     */
    void addOption(const std::string& option_name, Option::Type type, const std::string& help);

    /**
     * Parses command line
     *
     * @param[in] argc number of arguments
     * @param[in] argv array of arguments
     * @returns true if command line is parsed without error
     */
    bool parse(int argc, const char* argv[]);

    /**
     * Tells if option is set
     *
     * @param[in] opt_name name of option
     * @returns true if option is set
     */
    bool isSet(const std::string& opt_name);

    Option::Value get_value(const std::string& opt_name);

    /**
     * Get positional arguments
     *
     * @returns list of positional arguments if any
     */
    const std::vector<std::string>& get_positional() const { return m_pos_args; }

    /**
     * Autogenerated Usage
     */
    void usage() const;

    /* Deleted Functions */
    Options(const Options&)             = delete;
    Options(Options&&)                  = delete;
    Options& operator=(const Options&)  = delete;
    Options& operator=(Options&&)       = delete;

    private:
    cystructs::Tree<Option*> m_option_list;
    std::vector<std::string> m_pos_args;
};

#endif
