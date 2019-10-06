#ifndef _LOG_H
#define _LOG_H

#include <iostream>

class Log {
    public:
    template <typename... Args>
    static void d(const Args... args) { std::cout << "|DEBUG| "; display(args...); }
    template <typename... Args>
    static void e(const Args... args) { std::cout << "|ERROR| "; display(args...); }
    template <typename... Args>
    static void i(const Args... args) { std::cout << "|INFO| "; display(args...); }
    template <typename... Args>
    static void w(const Args... args) { std::cout << "|WARN| "; display(args...); }

    private:
    template <typename T, typename... Args>
    static void display(T first, Args... args) {
        std::cout << first;
        display(args...);
    }
    
    static void display() { std::cout << std::endl; }
};

#endif
