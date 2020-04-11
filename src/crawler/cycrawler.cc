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
    DIR *dir = opendir(path.c_str());
    if(!dir) {
        switch(errno) {
            case EACCES:
                Log::e(path, " Permisson denied");
                return {};
                break;
            case EMFILE:
                Log::e("Process limit for maxmimum open file reached");
                return {};
                break;
            case ENFILE:
                Log::e("System limit for maxmimum open file reached");
                return {};
                break;
            case ENOENT:
                Log::e(path, " does not exist");
                return {};
                break;
            case ENOMEM:
                Log::e("Insufficient memory");
                return {};
                break;
            case ENOTDIR:
                Log::e("Not a directory");
                return {};
                break;
        }
    }

    std::forward_list<std::string> file_list;
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
        }
        dirp = readdir(dir);
    }

    return file_list;
}
