#include <core/animations_queue.h>
#include "prison_connection.h"
#include "components/additions.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "managers/entity_manager.h"
#include "sender.h"
#include "common/animations.h"

prison_connection::prison_connection(std::uint32_t entity_id) : entity_id(entity_id) {

}

void prison_connection::use(std::uint32_t index_on) {

	if (used)
		return;

	auto enemy_id = board::at(index_on);
	auto caster_id = board::at(states::state_controller::selected_index_);

	auto prison_connection_holder = make_after_n_round_callback_holder(duration,
																	   [this, enemy_id, caster_id]() {

																		   remove_component(enemy_id, "prison_connection_effect");

																		   if (entity_manager::alive(caster_id)) {
																			   entities_with_effect.erase(std::remove(std::begin(entities_with_effect), std::end(entities_with_effect), enemy_id),
																										  std::end(entities_with_effect));
																		   }
																	   });

	if (has_component(enemy_id, "prison_connection_effect")) {
		entities_with_effect.erase(std::remove(std::begin(entities_with_effect), std::end(entities_with_effect), enemy_id),
								   std::end(entities_with_effect));
	}

	add_component(enemy_id, "prison_connection_effect", prison_connection_holder);
	entities_with_effect.push_front(enemy_id);

	std::int32_t number_of_entities_with_effect = static_cast<std::int32_t>(entities_with_effect.size());

	final_damage = base_damage + number_of_entities_with_effect * damage_per_entities_with_effect;

	std::cout << "final_damage: " << final_damage << "\n";

	sender::send(message_types::animation, animation_def::start_sorcerer_attack, entity_id);

	for (auto&& entity_with_effect : entities_with_effect) {

		if (entity_manager::alive(entity_with_effect)) {
			auto index = board::index_for(entity_with_effect);

			sender::send(message_types::animation, animation_def::prison_connection, index);

			damage_dealers::standard_damage_dealer(magic_damage(final_damage, board::at(index), entity_id));
		}
	}

	sender::send(message_types::animation, animation_def::end_sorcerer_attack, entity_id);

	used = true;
}