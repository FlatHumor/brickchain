#include <iostream>

#include "transaction.h"
#include "brick_chain.h"
#include "file_repository.h"

#ifdef _WIN32
#define BRICKCHAIN_PATH "C:\\Users\\Soy\\Documents\\chain"
#else
#define BRICKCHAIN_PATH "/home/mark/CLionProjects/brickchain/chain"
#endif // _WIN32

int main(int argc, char * argv[]) 
{
    std::string brickchain_path = BRICKCHAIN_PATH;
    std::string content = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
    transaction transaction("sender", "receiver", content);
    file_repository brick_repo = file_repository(brickchain_path);
    brick_chain brickchain;
    brickchain.link_repository(& brick_repo);
    brickchain.add_transaction(transaction);
    if (brickchain.is_valid())
        std::cout << "brick_chain valid" << std::endl;
    else
        std::cout << "brick_chain is invalid" << std::endl;
    //std::cout << transaction << std::endl;
    brickchain.unlink_repository();

//    std::string a = "1.brick";
//    std::shared_ptr<brick> s_brick(new brick());
//    chain.load_brick(s_brick.get(), a);
//    std::cout << "raw string:    " << transaction.get_guess() << std::endl;
//    std::cout << "loaded string: " << s_brick->get_transaction().get_guess() << std::endl;
//    std::cout << "raw hash:    " << brick_chain::build_hash(transaction.get_guess()) << std::endl;
//    std::cout << "loaded hash: " << brick_chain::build_hash(s_brick->get_transaction().get_guess()) << std::endl;
//    std::cout << * s_brick << std::endl;

    return 0;
}