#include <common/make_message.h>
#include "sabers.h"
#include "core/path_finder.h"
#include "core/states_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "sender.h"
#include "common/animations.h"

void sabers::prepare(std::uint32_t for_index)
{
	targets_.clear();

	states::state_controller::selected_index_ = for_index;
	board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

	states::state_controller::actual_targeting_type_ = target_types::enemy;
	states::state_controller::wait_for_action([this](std::uint32_t index)
	{
		return target(index);
	});
}

void sabers::target(std::uint32_t target_index)
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

		states::state_controller::actual_targeting_type_ = target_types::enemy;
		states::state_controller::wait_for_action([this](std::uint32_t index)
		{
			return target(index);
		});
	}
}

void sabers::use(std::uint32_t index_on)
{
	if (board::empty(index_on))
		return;

	auto used_from_index = states::state_controller::selected_index_;
	auto entity_id = board::at(used_from_index);

	sender::send(make_action_message("sabers", used_from_index, index_on));

	damage_dealers::standard_damage_dealer(melee_damage(damage, board::at(index_on), entity_id));
}