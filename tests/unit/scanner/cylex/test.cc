#include "cylex.h"

#include <chrono>

#include "cytest.h"

void analyseFile() {
    CyLex lex;
    auto start = std::chrono::system_clock::now();

    lex.addPattern("int");
    lex.addPattern("float");
    lex.readFile("text");
    lex.analyse();

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
//    Log::i("elapsed time: ", std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count());
}

int main() {
    cytest::Testcase t;
    t.add(analyseFile);
    t.run();
}
