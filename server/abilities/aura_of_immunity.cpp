#include <managers/entity_manager.h>
#include <managers/players_manager.h>
#include <effects/aura_of_immunity_effect.h>
#include <effects/auras_observer.h>
#include "aura_of_immunity.h"
#include "core/path_finder.h"
#include "core/board.h"
#include "components/additions.h"
#include "components/modification.h"
#include "sender.h"
#include "common/animations.h"
#include "moveable.h"

aura_of_immunity::aura_of_immunity(std::uint32_t entity_id)
		: entity_id(entity_id) {

	entity_manager::get(entity_id).get<modification>()->modify_damage_receiver_modifier_by(-damage_reduction_for_owner);

	auras_observer::add_aura(entity_id, std::make_shared<aura_of_immunity_effect>(damage_reduction_for_friends));


//	on_every_two_turns_from_this([entity_id = this->entity_id,
//			damage_reduction_for_friends = this->damage_reduction_for_friends,
//			damage_reduction_for_owner = this->damage_reduction_for_owner]() {
//
//		auto caster_index = board::index_for(entity_id);
//
//		std::vector<std::uint32_t> neighbors;
//		board_helper::neighboring_fields(caster_index, neighbors, false);
//
//		for (auto& index : neighbors) {
//			if (!board::empty(index)) {
//				if (players_funcs::enemy_entity(index)) {
//
//				} else if (players_funcs::player_entity(index)) {
//
//					auto friend_id = board::at(index);
//
//					if (!has_component(friend_id, "aura_of_immunity")) {
//						entity_manager::get(friend_id).get<modification>()->modify_damage_dealer_modifier_by(-damage_reduction_for_friends);
//					}
//
//					auto damage_reduction = damage_reduction_for_friends;
//
//					sender::send(message_types::animation, animation_def::aura_of_immunity, index);
//
//					auto aura_of_immunity_receiver = make_every_turn_callback_holder(2,
//																					 [damage_reduction, friend_id](const turn_callback_info& info) mutable {
//
//						if (info.ended) {
//
//							if (entity_manager::alive(friend_id)) {
//								entity_manager::get(friend_id).get<modification>()->modify_damage_dealer_modifier_by(damage_reduction);
//
//								sender::send(message_types::animation, animation_def::aura_of_immunity_break, board::index_for(friend_id));
//
//
//								remove_component(friend_id, "aura_of_immunity");
//							}
//						}
//					});
//
//					add_component(friend_id, "aura_of_immunity", aura_of_immunity_receiver);
//				}
//			}
//		}
//	});
}

std::string aura_of_immunity::hint() const {

	std::string desc;
	desc = "Aura Of Immunity - giant offers a nearby allies aure\n"
				   "which apply damage reduction of " + std::to_string(damage_reduction_for_friends) + ".\n"
			"Giant also has constant damage reduction by " + std::to_string(damage_reduction_for_owner) + ".";

	return std::move(desc);
}