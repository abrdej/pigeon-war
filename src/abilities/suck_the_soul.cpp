#include "suck_the_soul.h"

#include <core/board.h>
#include <server/sender.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <messages/make_message.h>
#include "damage_dealers.h"

suck_the_soul::suck_the_soul(std::uint32_t entity_id) {

    set_damage_receiver(entity_id, [this, entity_id](health_field& health_pack, const damage_pack& dmg) mutable {

        auto damage_value = dmg.damage_value;
        auto damage_for_soul_health = 0.25f * damage_value;

        auto souls_n = souls.size();

        for (auto&& soul_pack : souls) {
            auto enemy_id = souls.front().first;

			if (game::get<entity_manager>().alive(enemy_id)) {
				auto soul_health = souls.front().second;

				soul_health -= damage_for_soul_health;
				soul_health = std::max(0, soul_health);

				standard_healing(healing_to_base_health(soul_health, enemy_id));

				remove_effect(enemy_id, "sucked soul");
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
	used = true;

    auto used_from_index = game_control().selected_index_;
    auto caster_id = game_board().at(used_from_index);
    auto enemy_id = game_board().at(index_on);


    sender::send(make_action_message("drain", used_from_index, index_on));

    damage_dealers::standard_damage_dealer(melee_damage(damage, enemy_id, caster_id));

	if (!game::get<entity_manager>().alive(enemy_id)) {
		return;
	}

    if (has_effect(enemy_id, "sucked soul")) {
		remove_effect(enemy_id, "sucked soul");

	} else {
		sender::send(make_action_message("soul_out", index_on));

		auto suck_damage = damage_dealers::standard_damage_dealer(magic_damage(suck_amount, enemy_id, caster_id));

		if (!game::get<entity_manager>().alive(enemy_id)) {
			return;
		}

		auto sucked_soul_connection = make_after_n_round_callback_holder(duration,
																		 [enemy_id, caster_id, suck_damage, this]() mutable {

																			 sender::send(
                                                                                     make_action_message("soul_out",
                                                                                                         game_board().index_for(
                                                                                                                 enemy_id)));

																			 standard_healing(healing_to_base_health(suck_damage, enemy_id));

																			 if (game::get<entity_manager>().alive(caster_id)) {
																				 souls.erase(std::begin(souls) + souls_mapped[enemy_id]);
																				 souls_mapped.erase(enemy_id);
																			 }

																			 remove_effect(enemy_id,
																						   "sucked soul");
																		 });

		souls.emplace_back(enemy_id, suck_damage);
		souls_mapped.emplace(enemy_id, souls.size() - 1);

		auto sucked_soul = make_not_removable_negative_effect("sucked soul");
		sucked_soul->set_turn_connection(std::move(sucked_soul_connection));

		add_effect(enemy_id, sucked_soul);
	}
}