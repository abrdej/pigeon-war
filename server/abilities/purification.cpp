#include "purification.h"
#include "power_cost_ability.h"

#include <common/message_types.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <components/damage_taker.h>
#include <common/animations.h>
#include <sender.h>
#include <components/power_field.h>
#include <components/applied_effects.h>
#include <common/make_message.h>

purification::purification(std::uint32_t entity_id) : entity_id(entity_id) {}

void purification::use(std::uint32_t index_on) {

    if (used) {
        return;
    }

    if (!use_ability_at_the_expense_of_power(entity_id, power_cost)) {
        return;
    }

    auto friend_id = board::at(index_on);

    sender::send(make_animation_message("purification", index_on));

    remove_negative_effects(friend_id);

    used = true;
}
