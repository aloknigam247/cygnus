#ifndef BASE_CYPERF_H
#define BASE_CYPERF_H

#include <chrono>

#define PERF_TIMER(func) CyPerf::timerStart(); func; CyPerf::timerStop()

class CyPerf {
    public:
    static void timerStart();
    static void timerStop();

    private:
    static std::chrono::time_point<std::chrono::system_clock> begin;
};

#endif
