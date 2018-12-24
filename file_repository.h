//
// Created by mark on 12/23/18.
//

#ifndef BRICKCHAIN_FILE_REPOSITORY_H
#define BRICKCHAIN_FILE_REPOSITORY_H

#ifdef _WIN32
#define    PATH_SEPARATOR '\\'
#include <Windows.h>
#else
#define    PATH_SEPARATOR '/'
#include <dirent.h>
#endif

#include "repository.h"
#include <fstream>
#include <regex>



class file_repository : public repository
{
public:
    explicit file_repository(std::string &);
    void load_brick(brick *, int32_t &) override;
    void save_brick(brick &, int32_t &) override;
    std::vector<int32_t> get_identificators() override;
    void set_bricks_path(std::string);

private:
    std::string build_filepath(int32_t &);
    std::vector<std::string> get_brick_filenames();
    const std::string bricks_path;
    const std::string brick_extension = ".brick";
};


#endif //BRICKCHAIN_FILE_REPOSITORY_H
