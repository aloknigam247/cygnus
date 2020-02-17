#include "cycompile.h"

#include "cyparse.h"

CyCompile::CyCompile(std::string file) {
    CyParse parser;
    parser.parse(file);
}
