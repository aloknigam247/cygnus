#include "cyperf.h"

#include "log.h"

std::chrono::time_point<std::chrono::system_clock> CyPerf::begin;

void CyPerf::timerStart() {
    begin = std::chrono::system_clock::now();
}

void CyPerf::timerStop() {
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    Log::d(elapsed.count());
}
