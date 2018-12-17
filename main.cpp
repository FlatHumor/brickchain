#include <iostream>

#include "transaction.h"
#include "chain.h"

int main(int argc, char * argv[]) {
    std::string brickchain_path = "/home/mark/CLionProjects/brickchain/chain";
    std::string content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    Transaction transaction("sender", "receiver", content);
    Chain chain(brickchain_path);
    chain.add_transaction(transaction);
    if (chain.is_valid())
        std::cout << "Chain valid" << std::endl;
    else
        std::cout << "Chain is invalid" << std::endl;
    std::cout << transaction << std::endl;

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}