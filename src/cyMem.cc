#include <iostream>

void *operator new(std::size_t s) {
    void *p = std::malloc(s);

    if(!p)
        throw std::bad_alloc();

    return p;
}

void *operator new[](std::size_t s) {
    void *p = std::malloc(s);

    if(!p)
        throw std::bad_alloc();

    return p;
}

void operator delete(void *p) {
    std::free(p);
}

void operator delete[](void *p) {
    std::free(p);
}
