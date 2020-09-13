#include <forward_list>
#include <string>
#include <vector>

class CyCrawler {
    public:
    std::forward_list<std::string> crawl(std::string path, std::vector<std::string> exts);

    private:
    std::forward_list<std::string> createFileList(std::string path, std::vector<std::string> exts);
};
