#include <iostream>

void* operator new(const std::size_t pi_s) {
    void* p = std::malloc(pi_s);

    if(!p)
        throw std::bad_alloc();

    return p;
}

void* operator new[](const std::size_t pi_s) {
    void* p = std::malloc(pi_s);

    if(!p)
        throw std::bad_alloc();

    return p;
}

void operator delete(void*& pio_ptr) {
    std::free(pio_ptr);
    pio_ptr = nullptr;
}

void operator delete[](void*& pio_ptr) {
    std::free(pio_ptr);
    pio_ptr = nullptr;
}
