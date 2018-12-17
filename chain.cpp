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
        brick->get_nonce()++;
    }
}

bool Chain::is_valid() {
    std::vector<std::string> bricks_filenames = get_bricks_filenames();
    if (bricks_filenames.empty())
        return true;
    std::string previous_hash = DEFAULT_HASH;
    std::shared_ptr<Brick> s_brick(new Brick());
    for (const std::string & brick_filename : bricks_filenames)
    {
        load_brick(s_brick.get(), brick_filename);
        if (brick_filename == bricks_filenames.at(0)) {
            previous_hash = s_brick->get_header_hash();
            continue;
        }
        if (s_brick->get_previous_hash() != previous_hash) {
            std::cout << * s_brick << std::endl;
            return false;
        }
        previous_hash = s_brick->get_header_hash();
    }
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
    std::shared_ptr<Brick> s_prev_brick(new Brick());
    get_previous_brick(s_prev_brick.get());
    if (!s_prev_brick->is_empty())
    {
        prev_filename = s_prev_brick->get_filename();
        prev_hash = s_prev_brick->get_header_hash();
        curr_filename = increment_filename(prev_filename);
    }
    std::stringstream transaction_stream;
    std::stringstream brick_stream;
    transaction_stream << transaction.get_sender();
    transaction_stream << transaction.get_receiver();
    transaction_stream << transaction.get_content();
    transaction_stream << transaction.get_timestamp();
    std::string transaction_hash = build_hash(transaction_stream.str());
    std::shared_ptr<Brick> s_brick(new Brick());
    brick_stream << transaction_stream.str() << prev_hash << s_brick->get_timestamp();
    std::string new_brick_header_hash = build_hash(brick_stream.str());
    s_brick->set_previous_hash(prev_hash);
    s_brick->set_header_hash(new_brick_header_hash);
    s_brick->set_transaction(transaction);
    calculate_nonce(s_brick.get());
    save_brick(* s_brick, curr_filename);
}

std::vector<std::string> Chain::get_bricks_filenames() {
    const std::regex re("\\d+?\\.brick");
    DIR * directory;
    struct dirent * entry;
    std::vector<std::string> brick_filenames;
    int32_t brick_number;
    std::vector<int32_t> brick_numbers;
    if ((directory = opendir(bricks_path.c_str())) != nullptr)
    {
        while ((entry = readdir(directory)) != nullptr)
        {
            std::string filename = entry->d_name;
            std::smatch match;
            if (std::regex_search(filename, match, re)) {
                brick_number = std::stoi(filename);
                brick_numbers.push_back(brick_number);
            }
        }
    }
    std::sort(brick_numbers.begin(), brick_numbers.end());
    for (int32_t brick_number : brick_numbers)
    {
        std::stringstream brick_stream;
        brick_stream << brick_number << ".brick";
        brick_filenames.push_back(brick_stream.str());
    }
    return brick_filenames;
}

void Chain::load_brick(Brick * brick, const std::string & filename) {
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
        long brick_timestamp = std::stol(lines.at(4));
        brick->set_timestamp(brick_timestamp);
        transaction.set_sender(lines.at(5));
        transaction.set_receiver(lines.at(6));
        transaction.set_content(lines.at(7));
        long transaction_timestamp = std::stol(lines.at(8));
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
