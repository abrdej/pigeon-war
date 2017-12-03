#include "sabers.h"
#include "core/path_finder.h"
#include "core/states.h"
#include "core/board.h"
#include "abilities/bullet.h"
#include "animation/animation.h"
#include "animation/animation_impl.h"
#include "abilities/damage_dealers.h"
#include "managers/types_manager.h"

sabers::sabers()
{
	onEveryRound([this]() {
		used = false;
	});
}

void sabers::prepare(size_t for_index)
{
	targets_.clear();

	states::state_controller::selected_index_ = for_index;
	board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
	{
		return target(index);
	});
}

void sabers::target(size_t target_index)
{
	auto result = std::find(std::begin(targets_), std::end(targets_), target_index);
	if (result != std::end(targets_))
	{
		if (used)
			return;

		for (auto ti : targets_)
			use(ti);
		use(target_index);

		used = true;
	}
	else
	{
		targets_.push_back(target_index);

		board_helper::neighboring_fields(target_index,
			states::state_controller::possible_movements_, false);
		states::state_controller::possible_movements_.push_back(target_index);

		states::state_controller::actual_targeting_type_ = states::target_types::enemy;
		states::state_controller::wait_for_action([this](size_t index)
		{
			return target(index);
		});
	}
}

void sabers::use(size_t index_on)
{
	if (board::empty(index_on))
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	play_animation(used_from_index, index_on);

	damage_dealers::standard_damage_dealer(melee_damage(damage_, board::at(index_on), entity_id));

	// show damage animation // for example. -9 dmg
	//states::state_controller::target_fields(states::target_types::non);
}

void sabers::play_animation(size_t index_from, size_t index_on)
{
	auto entity_id = board::take(index_from);
	auto type = types_manager::component_for(entity_id);
	animation::player<animation::move>::launch(animation::move(index_from, index_on, type));
	animation::base_player::play();
	animation::player<animation::flash_bitmap>::launch(
		animation::flash_bitmap(index_on, std::chrono::milliseconds(150), "sabers_attack.png"));
	animation::base_player::play();
	animation::player<animation::move>::launch(animation::move(index_on, index_from, type));
	animation::base_player::play();
	board::give_back(entity_id, index_from);
}