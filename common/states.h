//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_STATES_H
#define PIGEONWAR_STATES_H

#include <limits>
#include "add_enum.h"

namespace states {

enum class states_types { waiting, wait_for_action };
enum class target_types { caster, enemy, friendly, neutral, moving, all, non };

static const std::uint64_t no_selected_index = std::numeric_limits<std::uint64_t>::max();

}

PACKET_ADD_ENUM(states::states_types)
PACKET_ADD_ENUM(states::target_types)

#endif //PIGEONWAR_STATES_H
