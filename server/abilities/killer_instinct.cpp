#include <managers/additions_manager.h>
#include <core/board.h>
#include <managers/directions_manager.h>
#include "killer_instinct.h"
#include "core/animations_queue.h"
#include "managers/abilities_manager.h"


killer_instinct::killer_instinct(sf::Uint64 entity_id)
		: entity_id(entity_id) {
}

void killer_instinct::prepare(sf::Uint64 for_index) {

	auto& enemy_abilities = abilities_manager::component_for(entity_id);
	auto moveable_ptr = std::static_pointer_cast<moveable>(enemy_abilities.type(abilities::ability_types::moving));

	if (!moveable_ptr->has_range()) {
		states::state_controller::possible_movements_.clear();
		return;
	}

	path_target_ability::prepare(for_index);

	auto possible_movements = std::move(states::state_controller::possible_movements_);

	for (auto&& index : possible_movements) {
		if (board::empty(index)) {
			states::state_controller::possible_movements_.push_back(index);
		}
	}
}

void killer_instinct::use(sf::Uint64 index) {

	if (used)
		return;

	sender::send(message_types::animation, animation_def::set_killer_instinct, entity_id);

	auto killer_instinct_receiver =
			turn::turn_system::every_turn([this]() mutable {

				additions_manager::remove_component(entity_id,
													"killer_instinct");

				sender::send(message_types::animation, animation_def::remove_killer_instinct, entity_id);
			});

	additions_manager::add_component(entity_id, "killer_instinct", killer_instinct_receiver);

	auto move_from_index = states::state_controller::selected_index_;

	auto entity_id = board::take(move_from_index);

	states::state_controller::selected_index_ = states::no_selected_index;

	sender::send(message_types::animation, animation_def::move, move_from_index, index);


	sf::Int32 from_col = board::to_pos(move_from_index).first;
	sf::Int32 to_col = board::to_pos(index).first;
	if (from_col != to_col)
	if (from_col - to_col < 0)
		directions_manager::turn_right(entity_id);
	else
		directions_manager::turn_left(entity_id);

	board::give_back(entity_id, index);

	states::state_controller::selected_index_ = index;
	states::state_controller::possible_movements_.clear();

	used = true;

	auto& enemy_abilities = abilities_manager::component_for(entity_id);
	auto moveable_ptr = std::static_pointer_cast<moveable>(enemy_abilities.type(abilities::ability_types::moving));
	moveable_ptr->remove_range();
}