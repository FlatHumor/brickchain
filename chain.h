//
// Created by mark on 12/9/18.
//

#ifndef BRICKCHAIN_CHAIN_H
#define BRICKCHAIN_CHAIN_H

#include <string>
#include <cstdint>
#include <vector>
#include "picosha2.h"
#include "brick.h"


class Chain
{
    const std::string DEFAULT_HASH = "E175E69A8312A66A7011C1DCCFC2CF69823BC2C52F58CA516F60698F02DAA1D6";
public:
    static std::string build_hash(std::string);
    static bool check_nonce(std::string, int32_t, std::string);
    static void calculate_nonce(Brick *);
    static Brick * get_previous_brick();
    void add_transaction(Transaction &);
    void set_bricks_path(std::string &);
    std::vector<std::string> get_bricks_filenames();

private:
    void save_brick(const Brick &);
    std::string bricks_path;
};


#endif //BRICKCHAIN_CHAIN_H
