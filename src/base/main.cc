/************************************************************************************
 * MIT License                                                                      *
 *                                                                                  *
 * Copyright (c) 2020 Alok Nigam                                                    *
 *                                                                                  *
 * Permission is hereby granted, free of charge, to any person obtaining a copy     *
 * of this software and associated documentation files (the "Software"), to deal    *
 * in the Software without restriction, including without limitation the rights     *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 * copies of the Software, and to permit persons to whom the Software is            *
 * furnished to do so, subject to the following conditions:                         *
 *                                                                                  *
 * The above copyright notice and this permission notice shall be included in all   *
 * copies or substantial portions of the Software.                                  *
 *                                                                                  *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR       *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,         *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE    *
 * SOFTWARE.                                                                        *
 ************************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <forward_list>
#include "options.h"
#include "cycrawler.h"
#include "cyl.h"
#include "cydb.h"
#include "cyparser.h"
#include "tsparser.h"
#include "utils.h"
#include "cyperf.h"

CyPerf global_perf(nullptr, nullptr);

int main(const int argc, const char* argv[]) {
    PERF_ME;
    Status status = Status::SUCCESS;
    Options opt;

    opt.addOption("-v", Option::BOOL, "version");
    status = opt.parse(argc, argv);

    if(status != Status::SUCCESS)
        return static_cast<int>(status);

    if(opt.isSet("-v")) {
        std::cout << "Cygnus " << MAKE_STRING(VERSION) << '\n';
    }

    if(const char *lang_dir; lang_dir = getenv("CYGNUS_LANG_DIR")) {
        std::cout << "lang_dir: " << lang_dir << '\n';
        CyCrawler crawler;
        std::forward_list<std::string> cyl_files = crawler.crawl(lang_dir, {".cyl"});

        // Download and compile tree sitter

        Cyl cyl;
        for(auto file: cyl_files)
            cyl.readCyl(file);

        CyDB db;
        db.connect("cygnus.db");
        for(auto filetype: cyl.filetypes()) {
            // FEAT: get directory to scan from commandline
            // FEAT: get filetypes from commandline
            for(auto file: crawler.crawl("./", cyl.fileExts(filetype))) {
                TsParser parser;
                // parser.setLangBlock(cyl.getLangBlock(filetype));
                parser.parse(file);

                // for(auto rec: digest->getRecords()) {
                //     db.addRecord(rec);
                // }
            }
        }
        db.disconnect();
    }

    CyDB db;
    db.connect("cygnus.db");
    if(argc == 2) {
        for(auto rec: db.lookup(argv[1])) {
            std::cout << rec << '\n';
        }
    }
    db.disconnect();
    return static_cast<int>(status);
}
