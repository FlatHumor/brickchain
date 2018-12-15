//
// Created by mark on 12/9/18.
//

#include "chain.h"

Chain::Chain(std::string & path):
    bricks_path(path) {}

std::string Chain::build_hash(std::string guess) {
    return picosha2::hash256_hex_string(guess);
}

std::string Chain::increment_filename(std::string & prev_filename) {
    std::stringstream filename_stream;
    int32_t prev_block_number = std::stoi(prev_filename);
    filename_stream << ++prev_block_number << ".brick";
    return filename_stream.str();
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
//        std::cout << "Nonce: " << brick->get_nonce() << std::endl;
        brick->get_nonce()++;
    }
}

bool Chain::validate() {
    return true;
}

void Chain::get_previous_brick(Brick * brick) {
    std::vector<std::string> bricks_filenames = get_bricks_filenames();
    if (!bricks_filenames.empty()) {

        load_brick(brick, bricks_filenames.back());
    }
}

void Chain::add_transaction(Transaction & transaction) {
    std::string prev_filename = "0.brick";
    std::string curr_filename = "0.brick";
    std::string prev_hash = DEFAULT_HASH;
    auto * prev_brick = new Brick();
    get_previous_brick(prev_brick);
    if (!prev_brick->is_empty())
    {
        prev_filename = prev_brick->get_filename();
        prev_hash = prev_brick->get_header_hash();
        curr_filename = increment_filename(prev_filename);
    }
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
    brick->set_transaction(transaction);
    calculate_nonce(brick);
    save_brick(* brick, curr_filename);
    delete prev_brick;
    delete brick;
}

std::vector<std::string> Chain::get_bricks_filenames() {
    const std::regex re("\\d+?\\.brick");
    DIR * directory;
    struct dirent * entry;
    std::vector<std::string> brick_filenames;
    if ((directory = opendir(bricks_path.c_str())) != nullptr)
    {
        while ((entry = readdir(directory)) != nullptr)
        {
            std::string filename = entry->d_name;
            std::smatch match;
            if (std::regex_search(filename, match, re))
                brick_filenames.push_back(filename);
        }
    }
    std::sort(brick_filenames.begin(), brick_filenames.end());
    return brick_filenames;
}

void Chain::load_brick(Brick * brick, std::string & filename) {
    std::string line;
    std::vector<std::string> lines;
    std::string brick_filename;
    std::ifstream brick_file(brick_filename.append(bricks_path).append("/").append(filename));
    if (brick_file.is_open())
    {
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
        brick->set_filename(filename);
    }
}

void Chain::save_brick(Brick & brick, std::string & filename) {
    std::string fullpath;
    std::ofstream brick_file(fullpath.append(bricks_path).append("/").append(filename));
    if (brick_file.is_open())
    {
        brick_file << brick.get_header_hash() << std::endl;
        brick_file << brick.get_previous_hash() << std::endl;
        brick_file << brick.get_nonce() << std::endl;
        brick_file << brick.get_bits() << std::endl;
        brick_file << brick.get_timestamp() << std::endl;
        Transaction transaction = brick.get_transaction();
        brick_file << transaction.get_sender() << std::endl;
        brick_file << transaction.get_receiver() << std::endl;
        brick_file << transaction.get_content() << std::endl;
        brick_file << transaction.get_timestamp() << std::endl;

        brick_file.close();
    }
}