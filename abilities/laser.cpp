#include "laser.h"
#include "damage_dealers.h"
#include <core/states.h>
#include <animation/animation.h>

laser::laser() {
	onEveryTurn([this](){
		used = false;
	});
}

void laser::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;

	board_helper::calc_straight(for_index, states::state_controller::possible_movements_,
								states::state_controller::possible_movements_costs_,
								range_, true);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void laser::use(size_t index_on) {

	if (used)
		return;

	auto used_from_index = states::state_controller::selected_index_;

	auto from_pos = board::to_pos(index_on);
	auto to_pos = board::to_pos(used_from_index);

	int hor_diff = static_cast<int>(from_pos.first) - static_cast<int>(to_pos.first);
	int ver_diff = static_cast<int>(from_pos.second) - static_cast<int>(to_pos.second);

	int xx = 0;
	int yy = 0;

	if (hor_diff != 0) {
		xx = (hor_diff > 0 ? 1 : -1) * range_;
	} else {
		yy = (ver_diff > 0 ? 1 : -1) * range_;
	}

	auto index_to_move = board::to_index(to_pos.first + xx, to_pos.second + yy);

	play_animation(used_from_index, index_to_move);

	if (hor_diff != 0) {
		for (int x = hor_diff > 0 ? 1 : -1; abs(x) <= abs(range_); x = hor_diff > 0 ? x + 1 : x - 1) {

			auto index = board::to_index(to_pos.first + x, to_pos.second);

			if (!board::empty(index))
				damage_dealers::standard_damage_dealer(damage_, index);
		}
	} else {
		for (int y = ver_diff > 0 ? 1 : -1; abs(y) <= abs(range_); y = ver_diff > 0 ? y + 1 : y - 1) {

			auto index = board::to_index(to_pos.first, to_pos.second + y);

			if (!board::empty(index))
				damage_dealers::standard_damage_dealer(damage_, index);
		}
	}

	used = true;
}

void laser::play_animation(size_t from_index, size_t to_index) {

	animation::player<animation::move>::launch
			(animation::move(from_index, to_index, typeid(*this)));
	animation::base_player::play();
}
