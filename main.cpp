#include <iostream>

#include "transaction.h"
#include "chain.h"

int main(int argc, char * argv[]) {
    std::string brickchain_path = "/home/mark/CLionProjects/brickchain/chain";
    Transaction transaction("sender", "receiver", "Hi, I am currently following a book about SFML");
    Chain chain;
    chain.add_transaction(transaction);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}