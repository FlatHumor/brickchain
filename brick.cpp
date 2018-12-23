//
// Created by mark on 12/9/18.
//

#include <chrono>
#include <string>
#include <cstdint>
#include "brick.h"

brick::brick() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    timestamp = ms.count();
}

std::int32_t brick::get_identificator() {
    return identificator;
}

std::string brick::get_header_hash() const {
    return header_hash;
}

std::string brick::get_previous_hash() const {
    return previous_hash;
}

int32_t & brick::get_nonce() {
    return nonce;
}

std::string brick::get_bits() {
    return bits;
}

transaction brick::get_transaction() {
    return brick_transaction;
}

std::string brick::get_version() {
    return VERSION;
}

long brick::get_timestamp() {
    return timestamp;
}

std::string brick::get_guess() {
    std::stringstream brick_stream;
    brick_stream << brick_transaction.get_guess() << previous_hash << timestamp;
    return brick_stream.str();
}

void brick::set_header_hash(std::string & _hash) {
    header_hash = _hash;
}

void brick::set_previous_hash(std::string & _hash) {
    previous_hash = _hash;
}

void brick::set_nonce(int32_t & _nonce) {
    nonce = _nonce;
}

void brick::set_bits(std::string & _bits) {
    bits = _bits;
}

void brick::set_transaction(transaction & t) {
    brick_transaction = t;
}

void brick::set_timestamp(long & t) {
    timestamp = t;
}

void brick::set_identificator(int32_t & ident) {
    identificator = ident;
}

bool brick::is_empty() {
    return brick_transaction.is_empty() || header_hash.length() == 0;
}

std::ostream & operator<<(std::ostream & os, brick & brick)
{
    os << "\n========== BRICK ===========" << std::endl
       << "IDENT:\t\t\t" << brick.get_identificator() << std::endl
       << "VERSION:\t\t" << brick.get_version() << std::endl
       << "HEADER HASH:\t" << brick.get_header_hash() << std::endl
       << "PREVIOUS_HASH:\t" << brick.get_previous_hash() << std::endl
       << "NONCE:\t\t\t" << brick.get_nonce() << std::endl
       << "BITS:\t\t\t" << brick.get_bits() << std::endl
       << "TIMESTAMP:\t\t" << transaction::timestamp_to_string(brick.get_timestamp()) << std::endl;

    return os;
}
