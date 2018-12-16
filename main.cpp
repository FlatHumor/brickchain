#include <iostream>

#include "transaction.h"
#include "chain.h"

int main(int argc, char * argv[]) {
    std::string brickchain_path = "/home/mark/CLionProjects/brickchain/chain";
    Transaction transaction("sender", "receiver", "Hi, I am currently following a book about SFML");
    Chain chain(brickchain_path);
    chain.add_transaction(transaction);
    if (chain.is_valid())
        std::cout << "Chain valid" << std::endl;
    else
        std::cout << "Chain is invalid" << std::endl;

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}