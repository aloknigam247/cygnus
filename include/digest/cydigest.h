#include "digest.h"
#include "cydb.h"
#include <vector>

class CyDigest: public Digest {
    public:
    void addRecord(Record r) { record_col.push_back(r); }
    std::vector<Record> getRecords() { return record_col; }

    private:
    std::vector<Record> record_col;
};
