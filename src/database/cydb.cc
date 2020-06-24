#include "cydb.h"
#include "log.h"

std::ostream& operator<<(std::ostream &out, const Record &rec) {
    out << rec.name << '\t' << rec.tag << '\t' << rec.file << '\t' << rec.loc << '\n';
    return out;
}

std::istream& operator>>(std::istream &in, Record &rec) {
    in >> rec.name >> rec.tag >> rec.file >> rec.loc;
    return in;
}

void CyDB::connect(std::string file) {
    db_file.open(file, std::ios::in | std::ios::out | std::ios::app);
}

void CyDB::disconnect() {
    if(db_file.is_open())
        db_file.close();
}

void CyDB::addRecord(const Record& rec) {
    if(db_file.is_open())
        db_file << rec;
}

std::forward_list<Record> CyDB::lookup(std::string name) {
    if(!db_file.is_open()) {
        Log::e("No database is connected");
        return {};
    }

    std::forward_list<Record> res;
    Record rec;
    while(db_file >> rec && !db_file.eof()) {
        if(rec.name == name)
            res.push_front(rec);
    }

    return res;
}
