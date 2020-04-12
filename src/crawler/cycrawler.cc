#include "cycrawler.h"

#include <sys/types.h>
#include <dirent.h>

#include <cstring>
#include <iostream>

#include "log.h"

std::forward_list<std::string> CyCrawler::crawl() {
    return createFileList(path);
}

std::forward_list<std::string> CyCrawler::createFileList(std::string path) {
    std::forward_list<std::string> file_list;
    DIR *dir = opendir(path.c_str());
    if(!dir) {
        switch(errno) {
            case EACCES:
                Log::e(path, " Permisson denied");
                break;
#ifdef EXTENDED_FEATURE
            case ENOENT:
                Log::e(path, " does not exist");
                break;
            case ENOTDIR:
                Log::e("Not a directory");
                break;
#endif
            default:
                Log::e("Unexpected error");
        }
    }
    else {
        dirent *dirp = readdir(dir);;
        while(dirp) {
            switch(dirp->d_type) {
                case DT_DIR:
                    if(strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, "..")) {
                        for( auto file: createFileList(path + '/' + dirp->d_name)) {
                                file_list.push_front(file);
                        }
                    }
                    break;
                case DT_REG:
                    file_list.push_front(path + '/' + dirp->d_name);
                    break;
                default:
                    std::cout << "Default case\n";
                    break;
            }
            dirp = readdir(dir);
        }
    }

    return file_list;
}
