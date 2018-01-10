#include <managers/health_manager.h>
#include <core/states_controller.h>
#include "protection_field.h"
#include "damage_dealers.h"

protection_field::protection_field(std::size_t entity_id) {

    onEveryTurn([this, entity_id]() {
        if (players_manager::get_active_player_id() == players_manager::player_for_entity(entity_id)) {
            is_active = true;
        }
    });

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

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

void protection_field::use(size_t index_on) {
    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto entity_id = board::at(used_from_index);

    sender::send(message_types::animation, animation_def::protection_field, used_from_index, index_on);

    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index_on), entity_id));

    used = true;
}