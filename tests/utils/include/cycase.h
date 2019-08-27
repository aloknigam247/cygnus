#include <string>
#include <vector>

typedef void (*caseType)();

namespace Test {
    void print(std::string msg);
}

class Testcase {
    private:
        std::vector<caseType> case_list;
    public:
        void add(caseType p);
        int run();
};
