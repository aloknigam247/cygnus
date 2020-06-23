#include <forward_list>

#include "cystring.h"

class CyCrawler {
    public:
    void set_path(CyString m_path) { path = m_path; }
    std::forward_list<CyString> crawl();

    private:
    std::forward_list<CyString> createFileList(CyString path);
    CyString path;
};
