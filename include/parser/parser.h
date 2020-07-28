#ifndef PARSER_H
#define PARSER_H
#include <string>

class Digest {
    public:
    void set_data(void* d) { data = d; }
    void* get_data() { return data; }

    private:
    void *data;
};

class Parser {
    public:
    virtual Digest* parse(std::string file) = 0;
};
#endif
