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
 * @file Log.h
 * @brief All logs from Cygnus should use this
 *
 * Provides logging for all types of logs thrown from Cygnus
 *
 * @author Alok Nigam
 */

#ifndef BASE_LOG_H
#define BASE_LOG_H

#include <iostream>

/**
 * @class Log
 * @brief Logs from Cygnus
 *
 * Implements the logging framework for all types of logs, debug, error, info, warning
 */
class Log { //TODO: use pack expansion instead of recursive calls
    public:
    /**
     * Prints the comma seperated arguments of any type that supports operator<<.
     * There is no whitespaces in between the comma seperated pairs and ends with newline.
     * Logs are followed by |DEBUG|.
     *
     * @tparam Args one or more types to print
     * @param[in] args list of comma seperated arguments
     */
    template <typename... Args>
    static void d(const Args... args) { std::cout << "|DEBUG| "; display(args...); }

    /**
     * Prints the comma seperated arguments of any type that supports operator<<.
     * There is no whitespaces in between the comma seperated pairs and ends with newline.
     * Logs are followed by |ERROR|.
     *
     * @tparam Args one or more types to print
     * @param[in] args list of comma seperated arguments
     */
    template <typename... Args>
    static void e(const Args... args) { std::cout << "|ERROR| "; display(args...); }

    /**
     * Prints the comma seperated arguments of any type that supports operator<<.
     * There is no whitespaces in between the comma seperated pairs and ends with newline.
     * Logs are followed by |INFO|.
     *
     * @tparam Args one or more types to print
     * @param[in] args list of comma seperated arguments
     */
    template <typename... Args>
    static void i(const Args... args) { std::cout << "|INFO| "; display(args...); }

    /**
     * Prints the comma seperated arguments of any type that supports operator<<.
     * There is no whitespaces in between the comma seperated pairs and ends with newline.
     * Logs are followed by |WARN|.
     *
     * @tparam Args one or more types to print
     * @param[in] args list of comma seperated arguments
     */
    template <typename... Args>
    static void w(const Args... args) { std::cout << "|WARN| "; display(args...); }

    private:
    /**
     * Variadic template to print logs
     *
     * @tparam args list of comman seperated arguments
     * @param[in] first first argument extracted from expandable argument
     * @param[in] args expandable argument
     */
    template <typename T, typename... Args>
    static void display(T first, Args... args) {
        std::cout << first;
        display(args...);
    }

    /**
     * Last function call of variadic template display
     */
    static void display() { std::cout << std::endl; }
};

#endif
