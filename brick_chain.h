//
// Created by mark on 12/9/18.
//

#ifndef BRICKCHAIN_BRICKCHAIN_H
#define BRICKCHAIN_BRICKCHAIN_H

#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include "picosha2.h"
#include "brick.h"
#include "chain.h"


class brick_chain : public chain
{
    const std::string DEFAULT_HASH = "E175E69A8312A66A7011C1DCCFC2CF69823BC2C52F58CA516F60698F02DAA1D6";
public:
    void link_repository(repository *) override;
    void unlink_repository() override;
    void add_transaction(transaction &) override;
    bool is_valid() override;

private:
    bool check_nonce(const std::string &, const int32_t &, const std::string &) override;
    void calculate_nonce(brick *) override;
    void get_previous_brick(brick *) override;
    std::string build_hash(std::string) override;
    static std::string increment_filename(std::string &);
    repository * brick_repository;
};


#endif //BRICKCHAIN_CHAIN_H
