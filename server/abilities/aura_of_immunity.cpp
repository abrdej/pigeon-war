#include <managers/entity_manager.h>
#include "aura_of_immunity.h"
#include "core/path_finder.h"
#include "core/board.h"
#include "managers/additions_manager.h"
#include "managers/modifications_manager.h"
#include "core/animations_queue.h"

aura_of_immunity::aura_of_immunity(std::size_t entity_id)
		: entity_id(entity_id) {

	modifications_manager::modify_damage_receiver_modifier_by(entity_id, -damage_reduction_for_owner);

	onEveryTurn([this]() {

		if (players_manager::get_active_player_id() == players_manager::player_for_entity(this->entity_id)) {

			auto caster_index = board::index_for(this->entity_id);

			std::vector<size_t> neighbors;
			board_helper::neighboring_fields(caster_index, neighbors, false);

			for (auto& index : neighbors) {
				if (!board::empty(index)) {
					if (players_funcs::enemy_entity(index)) {

					} else if (players_funcs::player_entity(index)) {

						auto friend_id = board::at(index);

						if (!additions_manager::has_component(friend_id, "aura_of_immunity")) {
							modifications_manager::modify_damage_receiver_modifier_by(friend_id, -damage_reduction_for_friends);
						}

						sender::send(message_types::animation, animation_def::aura_of_immunity, index);

						auto aura_of_immunity_receiver =
								turn::turn_system::every_turn([this, counter = 0, aura_last = 1, friend_id]() mutable {

									if (counter++ == aura_last) {

										if (entity_manager::alive(friend_id)) {
											modifications_manager::modify_damage_receiver_modifier_by(friend_id, damage_reduction_for_friends);

											sender::send(message_types::animation, animation_def::aura_of_immunity_break, board::index_for(friend_id));


											additions_manager::remove_component(friend_id,
																				"aura_of_immunity");
										}
									}
								});

						additions_manager::add_component(friend_id, "aura_of_immunity", aura_of_immunity_receiver);
					}
				}
			}
		}
	});
}

