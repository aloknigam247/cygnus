#ifndef PARSER_H
#define PARSER_H
#include <string>

template <typename RET>
class Parser {
    public:
    virtual RET parse(std::string file) = 0;
};
#endif
