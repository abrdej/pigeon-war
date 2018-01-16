#include <core/path_finder.h>
#include <managers/players_manager.h>
#include "surroundings.h"
#include "components/damage_taker.h"

surroundings::surroundings(std::uint64_t entity_id) {

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto index = board::index_for(entity_id);

        std::vector<std::uint64_t> neighbors;
        board_helper::neighboring_fields(index, neighbors, false);

        std::int32_t enemies_in_neighborhood = 0;
        for (auto&& neighbor : neighbors) {
            if (!board::empty(neighbor)) {
                if (players_funcs::player_entity(board::index_for(entity_id)) && players_funcs::enemy_entity(neighbor)) {
                    ++enemies_in_neighborhood;

                } else if (!players_funcs::player_entity(board::index_for(entity_id)) && players_funcs::player_entity(neighbor)) {
                    ++enemies_in_neighborhood;
                }
            }
        }

        auto final_damage = std::min(health_pack.health,
                                     std::max(min_damage, dmg.damage_value - enemies_in_neighborhood * damage_reduction));

        std::cout << "enemies_in_neighborhood: " << enemies_in_neighborhood << "\n";

        health_pack.health -= final_damage;

        return final_damage;
    });
}