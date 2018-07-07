#include <managers/entity_manager.h>
#include "ball_and_chain.h"
#include "components/applied_effects.h"
#include "core/board.h"
#include "moveable.h"
#include "damage_dealers.h"
#include "abilities.h"

ball_and_chain::ball_and_chain(std::uint32_t entity_id) : entity_id(entity_id) {

}

void ball_and_chain::use(std::uint32_t index_on) {

	if (used_)
		return;

	auto enemy_id = game::get<board>().at(index_on);

	auto abilities_ptr = game::get<entity_manager>().get(enemy_id).get<abilities>();

	auto moveable_ptr =  std::dynamic_pointer_cast<moveable_base>(abilities_ptr->of_type(ability_types::moving));
	if (moveable_ptr) {
		auto ball_and_chain_callback_id =
				moveable_ptr->set_move_callback([dealer_id = entity_id, dmg = damage_per_cost, enemy_id](std::uint32_t, std::uint32_t, std::int32_t cost) {
					damage_dealers::standard_damage_dealer(magic_damage(cost * dmg, enemy_id, dealer_id));
				});

		auto ball_and_chain_connection =
				make_after_n_round_callback_holder(duration,
												   [ball_and_chain_callback_id, enemy_id]() mutable {

													   auto inner_enemy_abilities_ptr = game::get<entity_manager>().get(enemy_id).get<abilities>();
													   auto inner_moveable_ptr = std::dynamic_pointer_cast<moveable_base>(inner_enemy_abilities_ptr->of_type(ability_types::moving));

													   if (inner_moveable_ptr) {
														   inner_moveable_ptr->remove_move_callback(ball_and_chain_callback_id);
													   }

													   remove_effect(enemy_id, "ball and chain");
												   });

		auto ball_and_chain_effect = make_negative_effect("ball and chain");
		ball_and_chain_effect->set_turn_connection(std::move(ball_and_chain_connection));

		add_effect(enemy_id, ball_and_chain_effect);

		sender::send(make_action_message("ball_and_chain", index_on));

		used_= true;
	}
}
