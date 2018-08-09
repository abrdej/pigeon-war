#include <messages/make_message.h>
#include "prison_connection.h"
#include "components/applied_effects.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "managers/entity_manager.h"
#include "server/sender.h"

prison_connection::prison_connection(std::uint32_t entity_id)
		: entity_id(entity_id) {}

void prison_connection::use(std::uint32_t index_on) {

	if (used)
		return;

	auto enemy_id = game_board().at(index_on);
	auto caster_id = game_board().at(game_control().selected_index_);

	auto prison_connection_connection = make_after_n_round_callback_holder(duration,
																		   [this, enemy_id, caster_id]() {

																			   remove_effect(enemy_id,
																							 "prison connection");

																			   if (game::get<entity_manager>().alive(caster_id)) {
																				   entities_with_effect.erase(std::remove(std::begin(entities_with_effect), std::end(entities_with_effect), enemy_id),
																											  std::end(entities_with_effect));
																			   }
																		   });

	auto prison_connection = make_negative_effect("prison connection");
	prison_connection->set_turn_connection(std::move(prison_connection_connection));
	prison_connection->set_on_destruction([this, caster_id, enemy_id]() {
		if (game::get<entity_manager>().alive(caster_id)) {
			entities_with_effect.erase(std::remove(std::begin(entities_with_effect), std::end(entities_with_effect), enemy_id),
									   std::end(entities_with_effect));
		}
	});

//	if (has_effect(enemy_id, "prison_connection_effect")) {
//		entities_with_effect.erase(std::remove(std::begin(entities_with_effect), std::end(entities_with_effect), enemy_id),
//								   std::end(entities_with_effect));
//	}
//	entities_with_effect.erase(std::remove_if(std::begin(entities_with_effect), std::end(entities_with_effect),
//											  [](std::uint32_t id) {
//												  return !game::get<entity_manager>().alive(id);
//											  }), std::end(entities_with_effect));

	add_effect(enemy_id, prison_connection);
	entities_with_effect.push_front(enemy_id);

	auto number_of_entities_with_effect = static_cast<std::int32_t>(entities_with_effect.size());

	final_damage = base_damage + number_of_entities_with_effect * damage_per_entities_with_effect;

	sender::send(make_action_message("start_sorcerer_attack", entity_id));

	for (auto&& entity_with_effect : entities_with_effect) {

		if (game::get<entity_manager>().alive(entity_with_effect)) {
			auto index = game_board().index_for(entity_with_effect);

			sender::send(make_action_message("prison_connection", index));

			damage_dealers::standard_damage_dealer(magic_damage(final_damage, game_board().at(index), entity_id));
		}
	}

	sender::send(make_action_message("end_sorcerer_attack", entity_id));

	used = true;
}