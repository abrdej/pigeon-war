#include <components/additions.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include "killer_instinct.h"
#include "core/animations_queue.h"
#include "sender.h"


killer_instinct::killer_instinct(std::uint32_t entity_id)
		: entity_id(entity_id) {
}

void killer_instinct::prepare(std::uint32_t for_index) {

	auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();

	auto moveable_ptr = std::static_pointer_cast<moveable>(abilities_ptr->type(abilities::ability_types::moving));

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

void killer_instinct::use(std::uint32_t index) {

	if (used)
		return;

	sender::send(message_types::animation, animation_def::set_killer_instinct, entity_id);

	auto killer_instinct_receiver =
			turn::turn_system::every_turn([this]() mutable {

				remove_component(entity_id, "killer_instinct");

				sender::send(message_types::animation, animation_def::remove_killer_instinct, entity_id);
			});

	add_component(entity_id, "killer_instinct", killer_instinct_receiver);

	auto move_from_index = states::state_controller::selected_index_;

	auto entity_id = board::take(move_from_index);

	states::state_controller::selected_index_ = states::no_selected_index;

	sender::send(message_types::animation, animation_def::move, move_from_index, index);

	board::give_back(entity_id, index);

	states::state_controller::selected_index_ = index;
	states::state_controller::possible_movements_.clear();

	used = true;

	auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();

	auto moveable_ptr = std::static_pointer_cast<moveable>(abilities_ptr->type(abilities::ability_types::moving));
	moveable_ptr->remove_range();
}