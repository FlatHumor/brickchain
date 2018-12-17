#include <utility>

//
// Created by mark on 12/9/18.
//

#include "transaction.h"

Transaction::Transaction() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    timestamp = ms.count();
}

Transaction::Transaction(std::string s, std::string r, std::string c) {
    sender = std::move(s);
    receiver = std::move(r);
    content = std::move(c);
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    timestamp = ms.count();
}

std::string Transaction::get_sender() {
    return sender;
}

std::string Transaction::get_receiver() {
    return receiver;
}

std::string Transaction::get_content() {
    return content;
}

long Transaction::get_timestamp() {
    return timestamp;
}

void Transaction::set_sender(std::string & _sender) {
    sender = _sender;
}

void Transaction::set_receiver(std::string & _receiver) {
    receiver = _receiver;
}

void Transaction::set_content(std::string & _content) {
    content = _content;
}

void Transaction::set_timestamp(long & t) {
    timestamp = t;
}

bool Transaction::is_empty() {
    return (sender.length() == 0 || receiver.length() == 0 || content.length() == 0);
}

std::string Transaction::timestamp_to_string(const long & timestamp) {
    using namespace std::chrono;
    milliseconds ms(timestamp);
    seconds sec = duration_cast<seconds>(ms);
    time_t tm = sec.count();
    std::string time_string(ctime(&tm));
    return time_string;
}

std::ostream & operator<<(std::ostream & os, Transaction & transaction) {
    os << "\n========== TRANSACTION ==========" << std::endl
       << "SENDER:\t\t" << transaction.get_sender() << std::endl
       << "RECEIVER:\t" << transaction.get_receiver() << std::endl
       << "CONTENT:\t" << transaction.get_content() << std::endl
       << "TIMESTAMP:\t" << Transaction::timestamp_to_string(transaction.get_timestamp()) << std::endl;
    return os;
}