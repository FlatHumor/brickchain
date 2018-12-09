//
// Created by mark on 12/9/18.
//

#include "transaction.h"

Transaction::Transaction() {
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    timestamp = (int32_t)ms.count();
}

Transaction::Transaction(std::string s, std::string r, std::string c) {
    sender = s;
    receiver = r;
    content = c;
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch());
    timestamp = (int32_t)ms.count();
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

int32_t Transaction::get_timestamp() {
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

void Transaction::set_timestamp(int32_t & t) {
    timestamp = t;
}

bool Transaction::is_empty() {
    return (sender.length() == 0 || receiver.length() == 0 || content.length() == 0);
}