#include <core/turn_system.h>
#include <managers/entity_manager.h>
#include "immortality.h"
#include "components/damage_taker.h"
#include "sender.h"
#include "common/animations.h"

immortality::immortality(std::uint64_t entity_id) : entity_id(entity_id) {

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto final_damage = std::min(health_pack.health, dmg.damage_value);
        health_pack.health -= final_damage;

        if (health_pack.health == 0) {
            set_destructible(entity_id, false);

            sender::send(message_types::animation, animation_def::set_immortality, entity_id);

            receiver = turn::turn_system::every_turn([this, entity_id, &health_pack, counter = 0]() mutable {
                if (counter++ == 1) {
                    set_destructible(entity_id, true);
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