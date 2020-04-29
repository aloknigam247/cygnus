#include "compiler/cycompile.h"

#include "scanner/cyparse.h"

CyCompile::CyCompile(std::string file) {
    CyParse parser;
    parser.parse(file);
}
