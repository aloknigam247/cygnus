#include "cydb.h"
#include "cytest.h"

void createDB() {
    CyDB db;
    db.connect("test.db");
    db.addRecord(Record("name", "tag", "test_file", 1));
    db.addRecord(Record("name", "tag", "test_file", 2));
    db.disconnect();
}

void lookupDB() {
    CyDB db;
    db.connect("test.db");

    std::cout << "Lookup: name\n";
    for(auto const &r: db.lookup("name")) {
        std::cout << r;
    }

    db.disconnect();
    db.lookup("name");
}

int main() {
    cytest::Testcase testcase;
    testcase.add(createDB);
    testcase.add(lookupDB);
    testcase.run();
    return 0;
}
