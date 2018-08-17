#include "immortality.h"

#include <components/damage_taker.h>
#include <managers/entity_manager.h>
#include <messages/make_message.h>
#include <server/sender.h>

immortality::immortality(std::uint32_t entity_id) : entity_id(entity_id) {

    set_damage_receiver(entity_id, [this](health_field& health_pack, const damage_pack& dmg) mutable {

        auto final_damage = std::min(health_pack.health, dmg.damage_value);
        health_pack.health -= final_damage;

        if (health_pack.health == 0) {
            set_destructible(this->entity_id, false);

            sender::send(make_action_message("set_immortality", this->entity_id));

            immortality_holder = make_after_n_round_callback_holder(duration, [this]() {
                set_destructible(this->entity_id, true);
                game::get<entity_manager>().destroy(this->entity_id);
            });
        }

        return final_damage;
    });
}
