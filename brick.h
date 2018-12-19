//
// Created by mark on 12/9/18.
//

#ifndef BRICKCHAIN_BRICK_H
#define BRICKCHAIN_BRICK_H

#include "transaction.h"


class Brick
{
    const std::string VERSION = "1.0";
public:
    Brick();
    std::string get_header_hash() const;
    std::string get_previous_hash() const;
    int32_t & get_nonce();
    std::string get_bits();
    Transaction get_transaction();
    std::string get_version();
    long get_timestamp();
    std::string get_guess();
    std::string get_filename();
    void set_header_hash(std::string &);
    void set_previous_hash(std::string &);
    void set_nonce(int32_t &);
    void set_bits(std::string &);
    void set_transaction(Transaction &);
    void set_timestamp(long &);
    void set_filename(const std::string &);
    bool is_empty();
    friend std::ostream & operator<<(std::ostream &, Brick &);

private:
    std::string header_hash;
    std::string previous_hash;
    int32_t nonce = 0;
    std::string bits = "0000";
    Transaction transaction;
    long timestamp;
    std::string filename;
};


#endif //BRICKCHAIN_BRICK_H
