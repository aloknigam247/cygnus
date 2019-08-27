#include <iostream>
#include <string>

class Log {
    private:
        void prnt(const std::string &msg) {std::cout << msg << '\n';}

    public:
        void D(const std::string &msg) { std::cout << "[DEBUG] "; prnt(msg);}
        void E(const std::string &msg) { std::cout << "[ERROR] "; prnt(msg);}
        void I(const std::string &msg) { std::cout << "[INFO] ";  prnt(msg);}
        void W(const std::string &msg) { std::cout << "[WARN] ";  prnt(msg);}
};
