#include "armor.h"
#include <managers/health_manager.h>

armor::armor(std::size_t entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, int damage) mutable {

        auto final_damage = std::min(std::min(health_pack.health, damage), max_damage);
        health_pack.health -= final_damage;

        return final_damage;
    });
}