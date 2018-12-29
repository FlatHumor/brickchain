#include <utility>

//
// Created by mark on 12/9/18.
//

#include "transaction.h"

transaction::transaction() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    timestamp = ms.count();
}

transaction::transaction(std::string & s, std::string & r, std::string & c)
{
    sender = s;
    receiver = r;
    content = c;
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    timestamp = ms.count();
}

std::string transaction::get_sender() {
    return sender;
}

std::string transaction::get_receiver() {
    return receiver;
}

std::string transaction::get_content() {
    return content;
}

long transaction::get_timestamp() {
    return timestamp;
}

std::string transaction::get_guess() {
    std::stringstream transaction_stream;
    transaction_stream << sender << receiver << content << timestamp;
    return transaction_stream.str();
}

void transaction::set_sender(std::string & _sender) {
    sender = _sender;
}

void transaction::set_receiver(std::string & _receiver) {
    receiver = _receiver;
}

void transaction::set_content(std::string & _content) {
    content = _content;
}

void transaction::set_timestamp(long & t) {
    timestamp = t;
}

bool transaction::is_empty() {
    return (sender.length() == 0 || receiver.length() == 0 || content.length() == 0);
}

std::string transaction::timestamp_to_string(const long & timestamp)
{
    using namespace std::chrono;
    milliseconds ms(timestamp);
    seconds sec = duration_cast<seconds>(ms);
    time_t tm = sec.count();
    std::string time_string(ctime(&tm));
    return time_string;
}

std::ostream & operator<<(std::ostream & os, transaction & transaction)
{
    os << "\n========== TRANSACTION ==========" << std::endl
       << "SENDER:\t\t" << transaction.get_sender() << std::endl
       << "RECEIVER:\t" << transaction.get_receiver() << std::endl
       << "CONTENT:\t" << transaction.get_content() << std::endl
       << "TIMESTAMP:\t" << transaction::timestamp_to_string(transaction.get_timestamp()) << std::endl;
    return os;
}