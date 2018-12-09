//
// Created by mark on 12/9/18.
//

#include "chain.h"

std::string Chain::build_hash(std::string guess) {
    return picosha2::hash256_hex_string(guess);
}

void Chain::set_bricks_path(std::string & path) {
    bricks_path = path;
}

bool Chain::check_nonce(std::string header_hash, int32_t nonce, std::string bits) {
    std::stringstream proof_stream;
    proof_stream << header_hash << nonce;
    std::string hash = build_hash(proof_stream.str());
    std::string first_bits = hash.substr(0, bits.length());
    return first_bits == bits;
}

void Chain::calculate_nonce(Brick * brick) {
    while (!check_nonce(brick->get_header_hash(), brick->get_nonce(), brick->get_bits())) {
        std::cout << "Nonce: " << brick->get_nonce() << std::endl;
        brick->get_nonce()++;
    }
}

Brick Chain::get_previous_brick() {
    auto * brick = new Brick();
    std::vector<std::string> bricks_filenames = get_bricks_filenames();
    if (!bricks_filenames.empty()) {
        std::sort(bricks_filenames.begin(), bricks_filenames.end());
        load_brick(brick, bricks_filenames.back());
    }
    return * brick;
}

void Chain::add_transaction(Transaction & transaction) {
    std::string prev_hash;
    if (get_previous_brick().is_empty())
        prev_hash = DEFAULT_HASH;
    std::stringstream transaction_stream;
    std::stringstream brick_stream;
    transaction_stream << transaction.get_sender();
    transaction_stream << transaction.get_receiver();
    transaction_stream << transaction.get_content();
    transaction_stream << transaction.get_timestamp();
    std::string transaction_hash = build_hash(transaction_stream.str());
    auto * brick = new Brick();
    brick_stream << transaction_stream.str() << prev_hash << brick->get_timestamp();
    std::string new_brick_header_hash = build_hash(brick_stream.str());
    brick->set_previous_hash(prev_hash);
    brick->set_header_hash(new_brick_header_hash);
    calculate_nonce(brick);
}

std::vector<std::string> Chain::get_bricks_filenames() {
    DIR * directory;
    struct dirent * entry;
    std::vector<std::string> brick_filenames;
    if ((directory = opendir(bricks_path.c_str())) != nullptr)
    {
        while ((entry = readdir(directory)) != nullptr)
        {
            std::string filename = entry->d_name;
            if (&filename[filename.length() - 5] == "brick")
                brick_filenames.push_back(filename);
        }
    }
    return brick_filenames;
}

void Chain::load_brick(Brick * brick, std::string & filename) {
    std::string line;
    std::vector<std::string> lines;
    std::ifstream brick_file(filename);
    if (brick_file.is_open()) {
        while (std::getline(brick_file, line))
            lines.push_back(line);
        Transaction transaction;
        brick->set_header_hash(lines.at(0));
        brick->set_previous_hash(lines.at(1));
        int32_t nonce = std::stoi(lines.at(2));
        brick->set_nonce(nonce);
        brick->set_bits(lines.at(3));
        int32_t brick_timestamp = std::stoi(lines.at(4));
        brick->set_timestamp(brick_timestamp);
        transaction.set_sender(lines.at(5));
        transaction.set_receiver(lines.at(6));
        transaction.set_content(lines.at(7));
        int32_t transaction_timestamp = std::stoi(lines.at(8));
        transaction.set_timestamp(transaction_timestamp);
        brick->set_transaction(transaction);
    }
}

void Chain::save_brick(const Brick & brick) {

}