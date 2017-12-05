#include <managers/health_manager.h>
#include <managers/entity_manager.h>
#include <core/path_finder.h>
#include "detonation.h"
#include "damage_dealers.h"

detonation::detonation(std::size_t entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto final_damage = std::min(health_pack.health, dmg.damage_value);
        health_pack.health -= final_damage;

        if (health_pack.health == 0) {
            std::vector<size_t> neighbors;
            board_helper::neighboring_fields(board::index_for(entity_id), neighbors, false);

            auto from_cr = board::to_pos(board::index_for(entity_id));
            from_cr.first -= 1;
            from_cr.second -= 1;

            board::take(board::index_for(entity_id));

            animation::player<animation::flash_bitmap>::launch(
                    animation::flash_bitmap(board::to_index(from_cr.first, from_cr.second),
                                            std::chrono::milliseconds(150),
                                            "detonation_anim.png"));
            animation::base_player::play();

            for (auto& index : neighbors) {
                if (!board::empty(index))
                    damage_dealers::standard_damage_dealer(ranged_damage(damage, board::at(index), entity_id));
            }
        }

        return final_damage;
    });
}