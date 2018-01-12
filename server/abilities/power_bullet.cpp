#include <managers/additions_manager.h>
#include "power_bullet.h"
#include "core/states_controller.h"
#include "managers/abilities_manager.h"
#include "damage_dealers.h"

void power_bullet::use(sf::Uint64 index_on) {

    if (used)
        return;

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);
    auto enemy_id = board::at(index_on);

    auto has_power_bullet_effect = additions_manager::has_component(enemy_id, "power_bullet_effect");

    sender::send(message_types::animation, animation_def::power_bullet, used_from_index, index_on);

    damage_dealers::standard_damage_dealer(magic_damage(has_power_bullet_effect ?
                                                        damage_with_power_bullet_effect : full_damage,
                                                        board::at(index_on), caster_id));

    auto damage_per_turn_receiver =
            turn::turn_system::every_turn([enemy_id, caster_id, counter = 0,
                                                  //damage = damage_per_turn,
                                                  max_counter = duration_of_effect]() mutable {

                if (++counter == max_counter) {

                    additions_manager::remove_component(enemy_id,
                                                            "power_bullet_effect");
                }
            });


    additions_manager::add_component(enemy_id,
                                     "power_bullet_effect",
                                     damage_per_turn_receiver);

    used = true;
}

std::string power_bullet::hint() const {

    std::string desc;
    desc = "Power Bullet - deals damage of " + std::to_string(full_damage) + ".\n"
            "It also applies the effect of power bullet to enemy for one turn.\n"
            "Enemies with power bullet effect receive only " + std::to_string(damage_with_power_bullet_effect) + " points of damage.";

    return std::move(desc);
}