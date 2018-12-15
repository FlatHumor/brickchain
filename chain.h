//
// Created by mark on 12/9/18.
//

#ifndef BRICKCHAIN_CHAIN_H
#define BRICKCHAIN_CHAIN_H

#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <fstream>
#include <regex>
#include <dirent.h>
#include "picosha2.h"
#include "brick.h"


class Chain
{
    const std::string DEFAULT_HASH = "E175E69A8312A66A7011C1DCCFC2CF69823BC2C52F58CA516F60698F02DAA1D6";
public:
    explicit Chain(std::string &);
    void add_transaction(Transaction &);
    bool validate();

private:
    static std::string build_hash(std::string);
    static bool check_nonce(std::string, int32_t, std::string);
    static void calculate_nonce(Brick *);
    void get_previous_brick(Brick *);
    void save_brick(Brick &, std::string &);
    void load_brick(Brick *, std::string &);
    static std::string increment_filename(std::string &);
    const std::string bricks_path;
    std::vector<std::string> get_bricks_filenames();
};


#endif //BRICKCHAIN_CHAIN_H
