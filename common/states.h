//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_STATES_H
#define PIGEONWAR_STATES_H

#include <limits>
#include "add_enum.h"

namespace states {

enum class states_types { waiting, wait_for_action };

static const std::uint32_t no_selected_index = std::numeric_limits<std::uint32_t>::max();

}

enum class target_types { caster, enemy, friendly, neutral, moving, all, non };

struct target_types_key_hash
{
    template <typename T>
    std::uint32_t operator()(T t) const
    {
        return static_cast<std::uint32_t>(t);
    }
};

PACKET_ADD_ENUM(states::states_types)
PACKET_ADD_ENUM(target_types)

#endif //PIGEONWAR_STATES_H
