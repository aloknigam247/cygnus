#ifdef EXTENDED_FEATURE
#include <forward_list>
#include <string>

class CyCrawler {
    public:
    void set_path(std::string m_path) { path = m_path; }
    std::forward_list<std::string> crawl();

    private:
    std::forward_list<std::string> createFileList(std::string path);
    std::string path;
};
#endif
