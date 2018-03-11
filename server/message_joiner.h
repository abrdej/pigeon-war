//
// Created by abrdej on 11.03.18.
//

#ifndef PIGEONWAR_MESSAGE_JOINER_H
#define PIGEONWAR_MESSAGE_JOINER_H

#include <iostream>
#include <string>
#include <vector>

class message_joiner {
    const std::string delimiter;
    std::string internal_buffer;

public:
    explicit message_joiner(std::string delimiter)
            : delimiter(std::move(delimiter)) {}

    std::vector<std::string> add_message_data(const std::string& data) {
        internal_buffer += data;
        std::vector<std::string> messages;


        size_t pos = 0;
        std::string message;
        while ((pos = internal_buffer.find(delimiter)) != std::string::npos) {
            message = internal_buffer.substr(0, pos);
            messages.push_back(message);
            internal_buffer.erase(0, pos + delimiter.length());
        }

        return std::move(messages);
    }
};

#endif //PIGEONWAR_MESSAGE_JOINER_H
