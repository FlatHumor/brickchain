//
// Created by mark on 12/9/18.
//

#ifndef BRICKCHAIN_TRANSACTION_H
#define BRICKCHAIN_TRANSACTION_H

#include <chrono>
#include <string>
#include <cstdint>
#include <iostream>

class Transaction
{
public:
    Transaction();
    Transaction(std::string, std::string, std::string);
    std::string get_sender();
    std::string get_receiver();
    std::string get_content();
    long get_timestamp();
    void set_sender(std::string &);
    void set_receiver(std::string &);
    void set_content(std::string &);
    void set_timestamp(long &);
    bool is_empty();
    static std::string timestamp_to_string(const long &);
    friend std::ostream & operator<<(std::ostream &, Transaction &);

private:
    std::string sender;
    std::string receiver;
    std::string content;
    long timestamp;
};


#endif //BRICKCHAIN_TRANSACTION_H
