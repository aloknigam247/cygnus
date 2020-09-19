#include <chrono>
#include <map>
#include <string>

#define PERF_ME CyPerf _perf(__PRETTY_FUNCTION__, __FILE__);

struct PerfData {
    std::string func;
    std::string file;
    double num_calls   = 0;
    double min_runtime = 0;
    double max_runtime = 0;
    double avg_runtime = 0;
};

class CyPerf {
    public:
    CyPerf(const char *func, const char *file);
    ~CyPerf();

    private:
    void addPerf(double runtime);
    void printPerf();
    static std::map<std::string, PerfData> perf_data_map;
    const char *m_func, *m_file;
    std::chrono::time_point<std::chrono::high_resolution_clock> entry_time;
};
