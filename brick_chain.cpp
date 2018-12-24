//
// Created by mark on 12/9/18.
//

#include "brick_chain.h"


std::string brick_chain::build_hash(std::string guess) {
    return picosha2::hash256_hex_string(guess);
}

void brick_chain::link_repository(repository * brick_repository) {
    this->brick_repository = brick_repository;
}

void brick_chain::unlink_repository() {
    brick_repository = nullptr;
}

bool brick_chain::check_nonce(const std::string & header_hash, const int32_t & nonce, const std::string & bits)
{
    std::stringstream proof_stream;
    proof_stream << header_hash << nonce;
    std::string hash = build_hash(proof_stream.str());
    std::string first_bits = hash.substr(0, bits.length());
    return first_bits == bits;
}

void brick_chain::calculate_nonce(brick * brick) {
    while (!check_nonce(brick->get_header_hash(), brick->get_nonce(), brick->get_bits())) {
        brick->get_nonce()++;
    }
}

bool brick_chain::is_valid()
{
    std::vector<int32_t > bricks_numbers = brick_repository->get_identificators();
    if (bricks_numbers.empty())
        return true;
    std::string previous_hash = DEFAULT_HASH;
    std::shared_ptr<brick> s_brick(new brick());
    std::string transaction_guess;
    std::string brick_guess;
    std::string brick_hash;
    for (auto & brick_number : bricks_numbers)
    {
        brick_repository->load_brick(s_brick.get(), brick_number);

        if (brick_number == bricks_numbers.at(0)) {
            previous_hash = s_brick->get_header_hash();
            continue;
        }

        transaction_guess = s_brick->get_transaction().get_guess();
        brick_guess = s_brick->get_guess();
        brick_hash = build_hash(brick_guess);

        if (s_brick->get_header_hash() != brick_hash)
        {
            std::cout << "VALIDATION FAILED ON HASH RECALCULATION" << std::endl;
            std::cout << "EXISTING HASH:\t\t" << s_brick->get_header_hash() << std::endl;
            std::cout << "RECALCULATED HASH:\t" << brick_hash << std::endl;
            return false;
        }

        if (s_brick->get_previous_hash() != previous_hash)
        {
            std::cout << "VALIDATION FAILED ON LINK CHECKING" << std::endl;
            std::cout << * s_brick << std::endl;
            return false;
        }

        if (!check_nonce(s_brick->get_header_hash(), s_brick->get_nonce(), s_brick->get_bits()))
        {
            std::cout << "VALIDATION FAILED ON NONCE CHECKING" << std::endl;
            std::cout << * s_brick << std::endl;
            return false;
        }

        previous_hash = s_brick->get_header_hash();
    }
    return true;
}

void brick_chain::get_previous_brick(brick * brick)
{
    std::vector<int32_t> brick_numbers = brick_repository->get_identificators();
    if (!brick_numbers.empty()) {
        brick_repository->load_brick(brick, brick_numbers.back());
    }
}

void brick_chain::add_transaction(transaction & transaction)
{
    int32_t prev_brick_number = 0;
    int32_t curr_brick_number = 0;
    std::string prev_hash = DEFAULT_HASH;
    std::shared_ptr<brick> s_prev_brick(new brick());
    get_previous_brick(s_prev_brick.get());
    if (!s_prev_brick->is_empty())
    {
        prev_brick_number = s_prev_brick->get_identificator();
        prev_hash = s_prev_brick->get_header_hash();
        curr_brick_number = prev_brick_number + 1;
    }
    std::shared_ptr<brick> s_brick(new brick());
    s_brick->set_previous_hash(prev_hash);
    s_brick->set_transaction(transaction);
    std::string new_brick_header_hash = build_hash(s_brick->get_guess());
    s_brick->set_header_hash(new_brick_header_hash);
    calculate_nonce(s_brick.get());
    brick_repository->save_brick(* s_brick, curr_brick_number);
}

