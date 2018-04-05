#include "repair.h"

#include <managers/entity_manager.h>
#include <components/health_field.h>
#include <components/damage_taker.h>
#include <abilities/damage_dealers.h>

repair::repair(std::uint32_t id)
        : entity_id(id) {

}

void repair::use(std::uint32_t on_index) {
    if (used_)
        return;

    sender::send(make_action_message("repair", board::index_for(entity_id)));

    standard_healing(healing_to_base_health(repair_amount, entity_id));

    used_ = true;
}