//
// Created by mark on 12/9/18.
//

#include <chrono>
#include <string>
#include <cstdint>
#include "brick.h"

Brick::Brick() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    timestamp = ms.count();
}

std::string Brick::get_header_hash() const {
    return header_hash;
}

std::string Brick::get_previous_hash() const {
    return previous_hash;
}

int32_t & Brick::get_nonce() {
    return nonce;
}

std::string Brick::get_bits() {
    return bits;
}

Transaction Brick::get_transaction() {
    return transaction;
}

std::string Brick::get_version() {
    return VERSION;
}

long Brick::get_timestamp() {
    return timestamp;
}

std::string Brick::get_guess() {
    std::stringstream brick_stream;
    brick_stream << transaction.get_guess() << previous_hash << timestamp;
    return brick_stream.str();
}

std::string Brick::get_filename() {
    return filename;
}

void Brick::set_header_hash(std::string & _hash) {
    header_hash = _hash;
}

void Brick::set_previous_hash(std::string & _hash) {
    previous_hash = _hash;
}

void Brick::set_nonce(int32_t & _nonce) {
    nonce = _nonce;
}

void Brick::set_bits(std::string & _bits) {
    bits = _bits;
}

void Brick::set_transaction(Transaction & t) {
    transaction = t;
}

void Brick::set_timestamp(long & t) {
    timestamp = t;
}

void Brick::set_filename(const std::string & f) {
    filename = f;
}

bool Brick::is_empty() {
    return transaction.is_empty() || header_hash.length() == 0;
}

std::ostream & operator<<(std::ostream & os, Brick & brick)
{
    os << "\n========== BRICK ===========" << std::endl
       << "VERSION:\t\t"     << brick.get_version() << std::endl
       << "HEADER HASH:\t"   << brick.get_header_hash() << std::endl
       << "PREVIOUS_HASH:\t" << brick.get_previous_hash() << std::endl
       << "NONCE:\t\t\t"     << brick.get_nonce() << std::endl
       << "BITS:\t\t\t"      << brick.get_bits() << std::endl
       << "TIMESTAMP:\t\t"   << Transaction::timestamp_to_string(brick.get_timestamp()) << std::endl
       << "FILENAME:\t\t"    << brick.get_filename() << std::endl;

    return os;
}
