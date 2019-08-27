#include "CyStream.h"

void CyStream::open(const std::string &filename, std::ios_base::openmode mode) {
    f.open(filename, mode);
    isOpen = true;
}

void CyStream::close() {
    f.close();
    isOpen = false;
}

CyStream::~CyStream() {
    if(isOpen)
        f.close();
}
