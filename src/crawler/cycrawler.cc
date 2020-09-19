#include "cycrawler.h"

#include <sys/types.h>
#include <dirent.h>

#include <cstring>
#include <iostream>
#include "log.h"

std::forward_list<std::string> CyCrawler::crawl(std::string path, std::vector<std::string> exts) {
    return createFileList(path, exts);
}

std::forward_list<std::string> CyCrawler::createFileList(std::string path, std::vector<std::string> exts) {
    std::forward_list<std::string> file_list;
    DIR *dir = opendir(path.c_str()); // TODO: Use c++ filesystem classes
    if(!dir) {
        switch(errno) {
            case EACCES:
                Log::e(path, " Permisson denied");
                break;
            case ENOENT:
                Log::e(path, " does not exist");
                break;
            case ENOTDIR:
                Log::e("Not a directory");
                break;
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
                        for( auto file: createFileList(path + '/' + dirp->d_name, exts)) {
                                file_list.push_front(file);
                        }
                    }
                    break;
                case DT_REG:
                    std::string str(dirp->d_name);
                    for(auto e: exts) {
                        if(str.ends_with(e)) {
                            file_list.push_front(path + '/' + dirp->d_name);
                            break;
                        }
                    }
                    break;
            }
            dirp = readdir(dir);
        }
        closedir(dir);
    }

    return file_list;
}
