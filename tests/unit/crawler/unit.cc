#include "cytest.h"

#include "cycrawler.h"

void crawl(std::string path) {
    Crawler crawler;
    crawler.set_path(path);

    try {
        auto file_list = crawler.crawl();

        std::cout << "Files found:\n";
        for(auto file: file_list) {
            std::cout << file << '\n';
        }
    }
    catch(not_exist) {
        std::cout << "Path: " << path << " does not exists\n";
    }
}

void dirNotExist() {
    crawl("test_dir_not_exist");
}

void dirEmpty() {
    crawl("test_dir_empty");
}

void dirExist() {
    crawl("test_dir_exist");
}

int main() {
    cytest::Testcase testcase;

    testcase.add(dirNotExist);
    testcase.add(dirEmpty);
    testcase.add(dirExist);
}
