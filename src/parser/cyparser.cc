#include "cyparser.h"

#include <fstream>
#include <streambuf>
#include <regex>
#include <iostream>

CyDigest* CyParser::parse(std::string file) {
    std::ifstream fstrm(file);
    fstrm.seekg(0, std::ios::end);
    size_t length = fstrm.tellg();
    fstrm.seekg(0, std::ios::beg);

    char *fstr = new char[length];
    fstrm.read(fstr, length);
    fstrm.close();

    std::string str(fstr);

    CyDigest *digest = new CyDigest;

    size_t lnum = 1;
    std::smatch res;
    std::regex parent_regex(lang_blk.parent_pattern, std::regex::egrep);
    while(std::regex_search(str, res, parent_regex)) {
        std::cout << lang_blk.parent_pattern << ": " <<  res.str() << '\n';
        for(char c: res.prefix().str())
            if(c == '\n')
                ++lnum;

        for(size_t i = 1; i < res.size(); ++i) {
            if(res[i].matched) {
                std::cout << lang_blk.child_pattern[i-1] << '\n';
                std::smatch sub_res;
                std::regex child_regex(lang_blk.child_pattern[i-1], std::regex::egrep);
                std::string s = res.str();
                std::regex_search(s, sub_res, child_regex);
                std::map<int, std::string> m = lang_blk.tag_pair_col[i-1];
                for(auto [pos, tag]: m) {
                    digest->addRecord(Record(sub_res[pos], tag, file, lnum));
                }
            }
        }

        str = res.suffix();
    }
    delete[] fstr;
    return digest;
}
