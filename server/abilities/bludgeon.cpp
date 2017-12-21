#include <core/states_controller.h>
#include "bludgeon.h"
#include "damage_dealers.h"

bludgeon::bludgeon() {
	onEveryRound([this]() {
		used_ = false;
	});
}

void bludgeon::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;

	board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
								states::state_controller::possible_movements_costs_,
								range);

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
	auto entity_id = board::at(used_from_index);

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

	damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(push_to_index), entity_id));

	states::state_controller::selected_index_ = set_on_index;
}

void bludgeon::play_animation(size_t from_index, size_t to_index, size_t set_on_index, size_t push_to_index)
{
	bool with_push = from_index != set_on_index;

	auto entity_id = board::take(from_index);

	animations_queue::push_animation(animation_types::move, from_index, to_index, entity_id, bitmap_key::none);

	board::give_back(entity_id, to_index);

	animations_queue::push_animation(animation_types::flash_bitmap, to_index, 150, 0, bitmap_key::bum);

	if (with_push) {
		entity_id = board::take(to_index);

		auto enemy_id = board::take(to_index);

		board::give_back(entity_id, set_on_index);

		animations_queue::push_animation(animation_types::move, to_index, push_to_index, entity_id, bitmap_key::none);

		board::give_back(enemy_id, push_to_index);

	} else {
		animations_queue::push_animation(animation_types::move, to_index, from_index, entity_id, bitmap_key::none);

		board::give_back(entity_id, from_index);
	}
}

