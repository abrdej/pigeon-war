#include <components/applied_effects.h>
#include <messages/make_message.h>
#include "power_bullet.h"
#include "core/game_controller.h"
#include "damage_dealers.h"
#include "server/sender.h"

void power_bullet::use(std::uint32_t index_on) {

    if (used)
        return;

    auto used_from_index = game_control().selected_index_;
    auto caster_id = game_board().at(used_from_index);
    auto enemy_id = game_board().at(index_on);

    auto has_power_bullet_effect = has_effect(enemy_id, "effect of a power bullet");

    sender::send(make_action_message("power_bullet", used_from_index, index_on));

    damage_dealers::standard_damage_dealer(magic_damage(has_power_bullet_effect ?
                                                        damage_with_power_bullet_effect : full_damage,
                                                        game_board().at(index_on), caster_id));

    if (game::get<entity_manager>().alive(enemy_id)) {
        auto power_bullet_effect_connection = make_after_n_round_callback_holder(duration_of_effect,
                                                                                 [enemy_id, caster_id]() mutable {
                                                                                     remove_effect(enemy_id,
                                                                                                   "effect of a power bullet");
                                                                                 });

        auto power_bullet_effect = make_not_removable_positive_effect("effect of a power bullet");
        power_bullet_effect->set_turn_connection(std::move(power_bullet_effect_connection));

        add_effect(enemy_id,
                   power_bullet_effect);
    }

    used = true;
}

std::string power_bullet::hint() const {

    std::string desc;
    desc = "Power Bullet - deals damage of " + std::to_string(full_damage) + ".\n"
            "It also applies the effect of power bullet to enemy for one turn.\n"
            "Enemies with power bullet effect receive only " + std::to_string(damage_with_power_bullet_effect) + " points of damage.";

    return std::move(desc);
}