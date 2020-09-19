#include "cyperf.h"
#include <fstream>

std::map<std::string, PerfData> CyPerf::perf_data_map;

CyPerf::CyPerf(const char *func, const char *file) {
    m_func = func;
    m_file = file;
    entry_time = std::chrono::high_resolution_clock::now();
}

CyPerf::~CyPerf() {
    auto exit_time = std::chrono::high_resolution_clock::now();
    double runtime = std::chrono::duration_cast<std::chrono::microseconds>(exit_time - entry_time).count();
    if(m_func)
        addPerf(runtime);
    else
        printPerf();
}

void CyPerf::addPerf(double runtime) {
    std::string func(m_func), file(m_file);

    if(auto it = perf_data_map.find(func+file); it != perf_data_map.end()) {
        PerfData &data = it->second;
        ++data.num_calls;
        if(runtime < data.min_runtime)
            data.min_runtime = runtime;
        else if(runtime > data.max_runtime)
            data.max_runtime = runtime;

        data.avg_runtime = (data.avg_runtime + runtime)/2;
    }
    else {
        PerfData data{func, file, 1, runtime, runtime, runtime};
        perf_data_map[func+file] = data;
    }
}

void CyPerf::printPerf() {
    std::ofstream perf_out("perfdata", std::ios::app);
    for(auto& [tag, data]: perf_data_map) {
        perf_out << data.func << "\t" << data.file << "\t" << data.num_calls << "\t" << data.min_runtime << "\t" << data.max_runtime << "\t" << data.avg_runtime << '\n';
    }
}
