#include <managers/entity_manager.h>
#include "aura_of_immunity.h"
#include "core/path_finder.h"
#include "core/board.h"
#include "components/additions.h"
#include "components/modification.h"
#include "sender.h"
#include "common/animations.h"

aura_of_immunity::aura_of_immunity(std::uint32_t entity_id)
		: entity_id(entity_id) {

	entity_manager::get(entity_id).get<modification>()->modify_damage_receiver_modifier_by(-damage_reduction_for_owner);

	onEveryTurn([entity_id = this->entity_id,
			damage_reduction_for_friends = this->damage_reduction_for_friends,
			damage_reduction_for_owner = this->damage_reduction_for_owner]() {

		if (players_manager::get_active_player_id() == players_manager::player_for_entity(entity_id)) {

			auto caster_index = board::index_for(entity_id);

			std::vector<std::uint32_t> neighbors;
			board_helper::neighboring_fields(caster_index, neighbors, false);

			for (auto& index : neighbors) {
				if (!board::empty(index)) {
					if (players_funcs::enemy_entity(index)) {

					} else if (players_funcs::player_entity(index)) {

						auto friend_id = board::at(index);

						if (!has_component(friend_id, "aura_of_immunity")) {
							entity_manager::get(friend_id).get<modification>()->modify_damage_dealer_modifier_by(-damage_reduction_for_friends);
						}

						sender::send(message_types::animation, animation_def::aura_of_immunity, index);

						auto aura_of_immunity_receiver =
								turn::turn_system::every_turn([damage_reduction_for_friends, counter = 0, aura_last = 1, friend_id]() mutable {

									if (counter++ == aura_last) {

										if (entity_manager::alive(friend_id)) {
											entity_manager::get(friend_id).get<modification>()->modify_damage_dealer_modifier_by(damage_reduction_for_friends);

											sender::send(message_types::animation, animation_def::aura_of_immunity_break, board::index_for(friend_id));


											remove_component(friend_id, "aura_of_immunity");
										}
									}
								});

						add_component(friend_id, "aura_of_immunity", aura_of_immunity_receiver);
					}
				}
			}
		}
	});
}

std::string aura_of_immunity::hint() const {

	std::string desc;
	desc = "Aura Of Immunity - giant offers a nearby allies aure\n"
				   "which apply damage reduction of " + std::to_string(damage_reduction_for_friends) + ".\n"
			"Giant also has constant damage reduction by " + std::to_string(damage_reduction_for_owner) + ".";

	return std::move(desc);
}