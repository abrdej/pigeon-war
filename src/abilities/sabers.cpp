#include <messages/make_message.h>
#include "sabers.h"
#include "core/path_finder.h"
#include "core/game_controller.h"
#include "core/board.h"
#include "damage_dealers.h"
#include "server/sender.h"

void sabers::prepare(std::uint32_t for_index)
{
	targets_.clear();

	game_control().selected_index_ = for_index;
	board_helper::neighboring_fields(for_index, game_control().possible_movements_, false);

	game_control().actual_targeting_type_ = target_types::enemy;
	game_control().wait_for_action([this](std::uint32_t index)
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
			game_control().possible_movements_, false);
		game_control().possible_movements_.push_back(target_index);

		game_control().actual_targeting_type_ = target_types::enemy;
		game_control().wait_for_action([this](std::uint32_t index)
		{
			return target(index);
		});
	}
}

void sabers::use(std::uint32_t index_on)
{
	if (game_board().empty(index_on))
		return;

	auto used_from_index = game_control().selected_index_;
	auto entity_id = game_board().at(used_from_index);

	sender::send(make_action_message("sabers", used_from_index, index_on));

	damage_dealers::standard_damage_dealer(melee_damage(damage, game_board().at(index_on), entity_id));
}