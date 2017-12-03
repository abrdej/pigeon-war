#include "grenade.h"

#include "core/states.h"
#include "core/path_finder.h"
#include "damage_dealers.h"
#include "animation/animation.h"
#include <chrono>

grenade::grenade()
	: used_(false)
{
}

void grenade::prepare(size_t for_index)
{
	states::state_controller::selected_index_ = for_index;

	path_finder path_finder(true);
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
		states::state_controller::possible_movements_costs_,
		range_);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return use(index);
	});
}

void grenade::use(size_t index_on)
{
	if (used_)
		return;

	used_ = true;
	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	std::vector<size_t> neightbords;
	board_helper::neighboring_fields(index_on, neightbords, false);

	play_animation(used_from_index, index_on, neightbords);

	damage_dealers::standard_damage_dealer(ranged_damage(damage_, board::at(index_on), entity_id));

	for (auto& index : neightbords)
	{
		if (!board::empty(index))
			damage_dealers::standard_damage_dealer(ranged_damage(damage_ / 2, board::at(index), entity_id));
	}
	// show damage animation // for example. -9 dmg
}

void grenade::play_animation(size_t from_index, size_t to_index, const std::vector<size_t>& neightbords)
{
	animation::player<animation::move>::launch(animation::move(from_index, to_index, typeid(*this)));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index, std::chrono::milliseconds(150), "bum.png"));
	for (auto& index : neightbords)
		animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(index, std::chrono::milliseconds(150), "shards.png"));
	animation::base_player::play();
}