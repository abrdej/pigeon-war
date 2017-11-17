#include "bomb.h"
#include "damage_dealers.h"
#include <core/states.h>
#include <core/board.h>
#include <managers/entity_manager.h>
#include <animation/animation.h>

void bomb_detonation::prepare(size_t for_index) {
	states::state_controller::actual_state_ = states::states_types::wait_for_action;
	states::state_controller::possible_movements_.push_back(for_index);
	states::state_controller::actual_targeting_type_ = states::target_types::caster;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void bomb_detonation::use(size_t for_index) {

	std::vector<size_t> neightbords;
	board_helper::neighboring_fields(for_index, neightbords, false);

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(for_index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();

	for (auto& index : neightbords)
	{
		if (!board::empty(index))
			damage_dealers::standard_damage_dealer(damage, index);
	}

	entity_manager::destroy(bomb_id);
}

bomb::bomb() : bombs(2) {

	onEveryTurn([this](){
		used = false;
	});
}

void bomb::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;
	states::state_controller::actual_state_ = states::states_types::wait_for_action;

	path_finder path_finder;
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
									   states::state_controller::possible_movements_costs_,
									   range);

	states::state_controller::actual_targeting_type_ = states::target_types::moving;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void bomb::use(size_t index) {

	if (used) {
		return;
	}

	used = true;

	auto bomb_id = entity_manager::create<bomb_instance>();
	auto player = players::active_player_name();
	players::add_entity_for_player(player, bomb_id);

	board::insert(index, bomb_id);

	bombs.push_back(std::shared_ptr<std::size_t>(new std::size_t(bomb_id), [](std::size_t *id){
		entity_manager::destroy(*id);
		delete id;
	}));
}