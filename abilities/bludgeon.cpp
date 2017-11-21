#include <core/states.h>
#include <animation/animation.h>
#include "bludgeon.h"
#include "damage_dealers.h"
#include "managers/types_manager.h"

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

	auto from_pos = board::to_pos(used_from_index);
	auto on_pos = board::to_pos(index_on);

	int x = from_pos.first - on_pos.first;
	int y = from_pos.second - on_pos.second;

	int push_x = on_pos.first - x;
	int push_y = on_pos.second - y;

	auto push_to_index = board::to_index(push_x, push_y);
	auto set_on_index = index_on;

	if (!board::is_valid(push_x, push_y)) { // || !board::empty(push_to_index)) {
		push_to_index = index_on;
		set_on_index = used_from_index;
	}

	play_animation(used_from_index, index_on, set_on_index, push_to_index);

	damage_dealers::standard_damage_dealer(damage_, board::at(push_to_index));

	states::state_controller::selected_index_ = set_on_index;
}

void bludgeon::play_animation(size_t from_index, size_t to_index, size_t set_on_index, size_t push_to_index)
{
	auto entity_id = board::take(from_index);

	auto type = types_manager::component_for(entity_id);


	animation::player<animation::move>::launch(animation::move(from_index, to_index, type));
	animation::base_player::play();
	board::give_back(entity_id, to_index);
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "bum.png"));
	animation::base_player::play();

	if (from_index == set_on_index) {
		entity_id = board::take(to_index);
		animation::player<animation::move>::launch(animation::move(to_index, set_on_index, type));
		animation::base_player::play();
		board::give_back(entity_id, set_on_index);

		//board::give_back(enemy_id, to_index);

	} else {

		auto enemy_id = board::take(to_index); //
		auto enemy_type = types_manager::component_for(enemy_id);

		animation::player<animation::move>::launch(animation::move(to_index, push_to_index, enemy_type));
		animation::base_player::play();
		board::give_back(enemy_id, push_to_index);
	}
}

