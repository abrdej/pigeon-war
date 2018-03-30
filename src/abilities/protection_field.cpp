#include <core/states_controller.h>
#include <messages/make_message.h>
#include "protection_field.h"
#include "damage_dealers.h"
#include "components/damage_taker.h"
#include "sender.h"

protection_field::protection_field(std::uint32_t entity_id) {

    on_every_two_turns_from_this([this, entity_id]() {
        is_active = true;
    });

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        if (is_active && !used) {
            is_active = false;
            return 0;

        } else {
            auto final_damage = std::min(health_pack.health, dmg.damage_value);
            health_pack.health -= final_damage;

            return final_damage;
        }
    });
}

void protection_field::use(std::uint32_t index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    sender::send(make_action_message("protection_field", used_from_index, index_on));

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    used = true;
}