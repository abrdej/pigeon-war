#include <core/board.h>
#include <common/message_types.h>
#include <sender.h>
#include <common/animations.h>
#include <components/additions.h>
#include <components/damage_taker.h>
#include "suck_the_soul.h"
#include "damage_dealers.h"

suck_the_soul::suck_the_soul(std::uint32_t entity_id) {

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto damage_value = dmg.damage_value;
        auto damage_for_soul_health = 0.25f * damage_value;

        auto souls_n = souls.size();

        for (auto&& soul_pack : souls) {
            auto enemy_id = souls.front().first;

			if (entity_manager::alive(enemy_id)) {
				auto soul_health = souls.front().second;

				soul_health -= damage_for_soul_health;
				soul_health = std::max(0, soul_health);

				entity_manager::get(enemy_id).get<damage_taker>()->heal(healing(soul_health,
																				enemy_id));

				remove_component(enemy_id,
								 "soul_suck");
			} else {
				souls_n -= 1;
			}
        }

		souls.clear();
		souls_mapped.clear();

        damage_value = damage_value - souls_n * damage_for_soul_health;
        damage_value = std::max(0, damage_value);

        auto final_damage = std::min(health_pack.health, damage_value);
        health_pack.health -= final_damage;

        return final_damage;
    });
}

void suck_the_soul::use(std::uint32_t index_on) {

    if (used) {
        return;
    }

    auto used_from_index = states::state_controller::selected_index_;
    auto caster_id = board::at(used_from_index);
    auto enemy_id = board::at(index_on);


    sender::send(message_types::animation, animation_def::drain, used_from_index, index_on);

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

    if (has_component(enemy_id, "soul_suck")) {
		remove_component(enemy_id,
			"soul_suck");

	} else {
		sender::send(message_types::animation, animation_def::soul_out, index_on);

		auto suck_damage = damage_dealers::standard_damage_dealer(magic_damage(suck_amount, enemy_id, caster_id));

		auto soul_suck_holder = make_after_n_round_callback_holder(duration,
			[enemy_id, caster_id, suck_damage, this]() mutable {

			sender::send(message_types::animation, animation_def::soul_out, board::index_for(enemy_id));

			entity_manager::get(enemy_id).get<damage_taker>()->heal(healing(suck_damage,
				enemy_id));

			if (entity_manager::alive(caster_id)) {
				souls.erase(std::begin(souls) + souls_mapped[enemy_id]);
				souls_mapped.erase(enemy_id);
			}

			remove_component(enemy_id,
				"soul_suck");
		});

		souls.emplace_back(enemy_id, suck_damage);
		souls_mapped.emplace(enemy_id, souls.size() - 1);

		add_component(enemy_id, "soul_suck", soul_suck_holder);
	}

    used = true;
}