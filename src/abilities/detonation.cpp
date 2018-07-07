#include <managers/entity_manager.h>
#include <core/path_finder.h>
#include <components/damage_taker.h>
#include "detonation.h"
#include "damage_dealers.h"

detonation::detonation(std::uint32_t entity_id) {

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto final_damage = std::min(health_pack.health, dmg.damage_value);
        health_pack.health -= final_damage;

        if (health_pack.health == 0) {
            std::vector<std::uint32_t> neighbors;
            board_helper::neighboring_fields(game::get<board>().index_for(entity_id), neighbors, false);

            auto entity_index = game::get<board>().index_for(entity_id);

            sender::send(make_action_message("detonation", entity_index));

            for (auto& index : neighbors) {
                if (!game::get<board>().empty(index))
                    damage_dealers::standard_damage_dealer(ranged_damage(damage, game::get<board>().at(index), entity_id));
            }
        }

        return final_damage;
    });
}