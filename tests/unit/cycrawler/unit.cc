#include "cytest.h"

#include "cycrawler.h"

void crawl(std::string path) {
    CyCrawler crawler;
    crawler.set_path(path);

    std::cout << "Files found:\n";
    for(auto file: crawler.crawl()) {
        std::cout << file << '\n';
    }
}

void dirNotExist() {
    crawl("test_dir_not_exist");
}

void dirExist() {
    crawl("test_dir");
}

void file() {
    crawl("test_dir/file");
}

void dirLink() {
    crawl("test_dir/dir_link");
}

void fileLink() {
    crawl("test_dir/file_link");
}

void brokenLink() {
    crawl("test_dir/broken_link");
}

void loopLink() {
    crawl("test_dir/loop_link");
}

/*
void noAccess() {
    crawl("test_dir/no_access");
}
*/

int main() {
    cytest::Testcase testcase;

    testcase.add(dirNotExist);
    testcase.add(dirExist);
    testcase.add(file);
    testcase.add(dirLink);
    testcase.add(fileLink);
    testcase.add(brokenLink);
    testcase.add(loopLink);
//    testcase.add(noAccess);

    testcase.run();
}
