#include "armor.h"
#include <managers/health_manager.h>

armor::armor(std::size_t entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto final_damage = std::min(std::min(health_pack.health, dmg.damage_value), max_damage);
        health_pack.health -= final_damage;

        return final_damage;
    });
}

std::string armor::hint() const {
    std::string desc;
    desc = "Armor - limits the maximum damage from a single attack\n"
                   "that Destroyer can receive to: " + std::to_string(max_damage) +".";
    return std::move(desc);
}