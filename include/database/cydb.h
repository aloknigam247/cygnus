#include <string>
#include <memory>
#include <forward_list>

#include "cyfile.h"

struct Record {
    std::string name, tag, file;
    int loc;

    Record() = default;
    Record(std::string n, std::string t, std::string f, int l): name(n), tag(t), file(f), loc(l) {}
    friend std::ostream& operator<<(std::ostream &out, const Record &rec);
    friend std::istream& operator>>(std::istream &in, Record &rec);
};

class CyDB {
    public:
    void connect(std::string file); // TODO: error check ?
    void disconnect();
    void addRecord(const Record &rec);
    std::forward_list<Record> lookup(std::string name); // TODO: can shared_ptr be used

    private:
    CyFile db_file;
};
