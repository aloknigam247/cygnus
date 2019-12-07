#ifndef NFA_H
#define NFA_H

#include "fa.h"

class NFA: public FA {
    public:
    void addPattern(const char* patt);
    void compile();

    private:
    std::vector<const char*> m_patt_list;
};

#endif
