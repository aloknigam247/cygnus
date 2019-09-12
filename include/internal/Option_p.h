#ifndef _OPTIONS_P_H
#define _OPTIONS_P_H

class Option {
    union Value;
    
    public:
    enum Type {
        CHAR,
        INT,
        STRING
    };

    Value get_value();
    Type get_type();

    private:
    union Value {
        char c;
        int t;
        char* s;
    };

    Type __type;
    Value __val;
};

#endif
