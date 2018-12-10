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
    timestamp = (int32_t)ms.count();
}

std::string Brick::get_header_hash() {
    return header_hash;
}

std::string Brick::get_previous_hash() {
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

int32_t Brick::get_timestamp() {
    return timestamp;
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

void Brick::set_timestamp(int32_t & t) {
    timestamp = t;
}

void Brick::set_filename(std::string & f) {
    filename = f;
}

bool Brick::is_empty() {
    return transaction.is_empty() || header_hash.length() == 0;
}