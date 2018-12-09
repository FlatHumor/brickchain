//
// Created by mark on 12/9/18.
//

#ifndef BRICKCHAIN_TRANSACTION_H
#define BRICKCHAIN_TRANSACTION_H

#include <string>
#include <cstdint>

class Transaction
{
public:
    Transaction();
    Transaction(std::string, std::string, std::string);
    std::string get_sender();
    std::string get_receiver();
    std::string get_content();
    int32_t get_timestamp();
    void set_sender(std::string &);
    void set_receiver(std::string &);
    void set_content(std::string &);

private:
    std::string sender;
    std::string receiver;
    std::string content;
    int32_t timestamp;
};


#endif //BRICKCHAIN_TRANSACTION_H
