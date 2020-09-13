#include "cyl.h"
#include "cylgrammar.h"
#include "bisonparser.h"
#include <iostream>
#include <cstring>

Status Cyl::readCyl(std::string cyl_file) {
    BisonParser *parser = new BisonParser;
    Digest *d = parser->parse(cyl_file);
    if(!d)
        return Status::CYL_PARSE_ERROR;

    CylGrammar *data = (CylGrammar*)d->get_data();

    LangBlock lb;
    std::string str2 = "(";
    std::map<int, std::string> tag_pair;
    PattTagStmtList *cur_stmt = data->patt_stmt_head;

    int beg = 0;
    for(int i=0, len=0; data->ext[i] != '\0'; ++i, ++len) {
        if(data->ext[i] == ',') {
            lb.exts.push_back(std::string(data->ext, beg, len));
            len = 0;
            beg = i+1;
        }
    }
    if(data->ext[beg] != '\0') {
        lb.exts.push_back(std::string(data->ext + beg));
    }

    while(cur_stmt) {
        printf("STMT TAG: %s\n", cur_stmt->stmt_tag);
        PattTagList *cur_tag = cur_stmt->patt_tag_list;

        std::string str1 = "";
        int i=1;
        tag_pair.clear();
        while(cur_tag) {
            printf("PATT: %s TAG: %s\n", cur_tag->patt, cur_tag->tag);
            str1 += cur_tag->patt;
            str2.append(cur_tag->patt+1, strlen(cur_tag->patt)-2);
            if(cur_tag->tag)
                tag_pair[i] = std::string(cur_tag->tag);
            cur_tag = cur_tag->next;
            ++i;
        }
        lb.child_pattern.push_back(str1);
        str2 += ")|(";
        cur_stmt = cur_stmt->next;
        lb.tag_pair_col.push_back(tag_pair);
    }
    str2.pop_back();
    str2.pop_back();
    lb.parent_pattern = str2;
    lang_coll[lb.exts[0]] = lb;

    return Status::SUCCESS;
}

LangBlock Cyl::getLangBlock(std::string filetype) {
    return lang_coll[filetype];
}

std::vector<std::string> Cyl::filetypes() {
    std::vector<std::string> list;
    for(auto [key, value]: lang_coll) {
        list.push_back(key);
    }
    return list;
}
