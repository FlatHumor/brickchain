//
// Created by mark on 12/23/18.
//

#ifndef BRICKCHAIN_CHAIN_H
#define BRICKCHAIN_CHAIN_H

#include "repository.h"

class chain
{
public:
    virtual void link_repository(repository *) = 0;
    virtual void unlink_repository() = 0;
    virtual void add_transaction(transaction &) = 0;
    virtual bool is_valid() = 0;

private:
    virtual bool check_nonce(const std::string &, const int32_t &, const std::string &) = 0;
    virtual void calculate_nonce(brick *) = 0;
    virtual void get_previous_brick(brick *) = 0;
    virtual std::string build_hash(std::string) = 0;
};

#endif //BRICKCHAIN_CHAIN_H
