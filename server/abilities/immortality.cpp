#include <managers/health_manager.h>
#include <core/turn.h>
#include <managers/entity_manager.h>
#include "immortality.h"

immortality::immortality(sf::Uint64 entity_id) : entity_id(entity_id) {

    healths_manager::set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto final_damage = std::min(health_pack.health, dmg.damage_value);
        health_pack.health -= final_damage;

        if (health_pack.health == 0) {
            healths_manager::set_destructible(entity_id, false);

            sender::send(message_types::animation, animation_def::set_immortality, entity_id);

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

std::string immortality::hint() const {

    std::string desc;
    desc = "Immortality - when the health of the warrior drops to zero\n"
            "the warrior becomes immortal for one more turn.";

    return std::move(desc);

}