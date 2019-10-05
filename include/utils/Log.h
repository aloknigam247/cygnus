#include <iostream>

class Log {
    public:
    template <typename T>
    static void d(const T pi_msg) { std::cout << "|DEBUG| " << pi_msg << '\n'; }
    template <typename T>
    static void e(const T pi_msg) { std::cout << "|ERROR| " << pi_msg << '\n'; }
    template <typename T>
    static void i(const T pi_msg) { std::cout << "|INFO| " << pi_msg << '\n';  }
    template <typename T>
    static void w(const T pi_msg) { std::cout << "|WARN| " << pi_msg << '\n';  }
};
