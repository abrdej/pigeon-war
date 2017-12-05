#include <managers/health_manager.h>
#include <core/turn.h>
#include <managers/entity_manager.h>
#include "immortality.h"

immortality::immortality(std::size_t entity_id) : entity_id(entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto final_damage = std::min(health_pack.health, dmg.damage_value);
        health_pack.health -= final_damage;

        //std::cout << "destructible: " << health_pack.health << "\n";

        if (health_pack.health == 0) {
            healths_manager::set_destructible(entity_id, false);
            receiver = turn::turn_system::every_turn([this, entity_id, &health_pack, counter = 0]() mutable {
                if (counter++ == 1) {
                    healths_manager::set_destructible(entity_id, true);
                    entity_manager::destroy(entity_id);
                }
            });
        }

        return final_damage;
    });
}