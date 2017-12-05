#include <abilities/moveable.h>
#include "command_manager.h"

command_type command_decoder(const command_data& data) {
    if (data.name == "move_entity") {
        return move_command{data.entity_id, data.from_index, data.to_index};
    }
}

std::queue<command_type> command_manager::command_queue;
std::queue<command_data> command_manager::command_data_queue;