/**
 * @file Log.h
 * @brief All logs from Cygnus should use this
 *
 * Provides logging for all types of logs thrown from Cygnus
 *
 * @author Alok Nigam
 */

#ifndef _LOG_H
#define _LOG_H

#include <iostream>

/**
 * @class Log
 * @brief Logs from Cygnus
 *
 * Implements the logging framework for all types of logs, debug, error, info, warning
 */
class Log {
    public:
    /**
     * Prints the comma seperated arguments of any type that supports operator<<.
     * There is no whitespaces in between the comma seperated pairs and ends with newline.
     * Logs are followed by |DEBUG|.
     *
     * @tparam Args one or more types to print
     * @param[in] pi_args list of comma seperated arguments
     */
    template <typename... Args>
    static void d(const Args... pi_args) { std::cout << "|DEBUG| "; display(pi_args...); }

    /**
     * Prints the comma seperated arguments of any type that supports operator<<.
     * There is no whitespaces in between the comma seperated pairs and ends with newline.
     * Logs are followed by |ERROR|.
     *
     * @tparam Args one or more types to print
     * @param[in] pi_args list of comma seperated arguments
     */
    template <typename... Args>
    static void e(const Args... pi_args) { std::cout << "|ERROR| "; display(pi_args...); }

    /**
     * Prints the comma seperated arguments of any type that supports operator<<.
     * There is no whitespaces in between the comma seperated pairs and ends with newline.
     * Logs are followed by |INFO|.
     *
     * @tparam Args one or more types to print
     * @param[in] pi_args list of comma seperated arguments
     */
    template <typename... Args>
    static void i(const Args... pi_args) { std::cout << "|INFO| "; display(pi_args...); }

    /**
     * Prints the comma seperated arguments of any type that supports operator<<.
     * There is no whitespaces in between the comma seperated pairs and ends with newline.
     * Logs are followed by |WARN|.
     *
     * @tparam Args one or more types to print
     * @param[in] pi_args list of comma seperated arguments
     */
    template <typename... Args>
    static void w(const Args... pi_args) { std::cout << "|WARN| "; display(pi_args...); }

    private:
    /**
     * Variadic template to print logs
     *
     * @tparam args list of comman seperated arguments
     * @param[in] pi_first first argument extracted from expandable argument
     * @param[in] pi_args expandable argument
     */
    template <typename T, typename... Args>
    static void display(T pi_first, Args... pi_args) {
        std::cout << pi_first;
        display(pi_args...);
    }

    /**
     * Last function call of variadic template display
     */
    static void display() { std::cout << std::endl; }
};

#endif
