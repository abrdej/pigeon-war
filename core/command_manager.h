//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_COMMAND_MANAGER_H
#define PIGEONWAR_COMMAND_MANAGER_H

#include <functional>
#include <queue>

struct command_data {
    std::string name;
    std::size_t entity_id;
    std::size_t from_index;
    std::size_t to_index;
};

using command_type = std::function<void()>;

template <typename Command>
command_data command_encoder(const Command& command);

command_type command_decoder(const command_data& data);

struct command_manager {

    static std::queue<command_type> command_queue;
    static std::queue<command_data> command_data_queue;

    static void handle_command(const command_data& data) {
        command_queue.push(command_decoder(data));
    }

    template <typename Command>
    static void send_command(const Command& command) {
        command_data_queue.push(command_encoder(command));
    }

    static void execute() {
        command_data& command_data = command_data_queue.front();
        handle_command(command_data);
        command_data_queue.pop();

        command_type& command = command_queue.front();
        command();
        command_queue.pop();
    }
};


#endif //PIGEONWAR_COMMAND_MANAGER_H
