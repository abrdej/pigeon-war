//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_STATES_H
#define PIGEONWAR_STATES_H

#include <rpc/msgpack.hpp>
#include "add_enum.h"

namespace states {

enum class states_types { waiting, wait_for_action };
enum class target_types { caster, enemy, friendly, neutral, moving, all, non };

static const std::size_t no_selected_index = std::numeric_limits<std::size_t>::max();

}

MSGPACK_ADD_ENUM(states::states_types);
MSGPACK_ADD_ENUM(states::target_types);

PACKET_ADD_ENUM(states::states_types)
PACKET_ADD_ENUM(states::target_types)

#endif //PIGEONWAR_STATES_H
