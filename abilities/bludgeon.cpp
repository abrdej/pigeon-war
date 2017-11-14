#include <core/states.h>
#include <animation/animation.h>
#include "bludgeon.h"
#include "damage_dealers.h"

bludgeon::bludgeon() {
	onEveryTurn([this](){
		used_ = false;
	});
}

void bludgeon::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;

	board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
								states::state_controller::possible_movements_costs_,
								range_);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void bludgeon::use(size_t index_on)
{
	if (used_)
		return;

	used_ = true;
	auto used_from_index = states::state_controller::selected_index_;

	auto col_row_from = board::to_col_row(used_from_index);
	auto col_row_on = board::to_col_row(index_on);

	int x = col_row_from.first - col_row_on.first;
	int y = col_row_from.second - col_row_on.second;

	auto push_to_index = board::to_index(col_row_on.first - x, col_row_on.second - y);

	play_animation(used_from_index, index_on, push_to_index);

	damage_dealers::standard_damage_dealer(damage_, push_to_index);

	states::state_controller::selected_index_ = index_on;
}

void bludgeon::play_animation(size_t from_index, size_t to_index, size_t push_to_index)
{
	auto entity_id = board::take(from_index);
	auto enemy_id = board::take(to_index);

	auto type = types_manager::component_for(entity_id);
	auto enemy_type = types_manager::component_for(enemy_id);

	animation::player<animation::move>::launch(animation::move(from_index, to_index, type));
	animation::base_player::play();
	board::give_back(entity_id, to_index);
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();
	animation::player<animation::move>::launch(animation::move(to_index, push_to_index, enemy_type));
	animation::base_player::play();
	board::give_back(enemy_id, push_to_index);
}

