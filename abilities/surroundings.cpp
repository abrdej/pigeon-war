#include <managers/health_manager.h>
#include <core/path_finder.h>
#include <core/players.h>
#include "surroundings.h"

surroundings::surroundings(std::size_t entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto index = board::index_for(entity_id);

        std::vector<std::size_t> neighbors;
        board_helper::neighboring_fields(index, neighbors, false);

        int enemies_in_neighborhood = 0;
        for (auto&& neighbor : neighbors) {
            if (!board::empty(neighbor)) {
                auto neighbor_id = board::at(index);
                if (players_funcs::enemy_entity(neighbor_id)) {
                    ++enemies_in_neighborhood;
                }
            }
        }

        auto final_damage = std::min(health_pack.health,
                                              std::max(min_damage, dmg.damage_value - enemies_in_neighborhood * damage_reduction));
        health_pack.health -= final_damage;

        return final_damage;
    });
}