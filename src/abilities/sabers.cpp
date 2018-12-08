#include <abilities/sabers.h>

#include <abilities/damage_dealers.h>
#include <core/board.h>
#include <core/game_controller.h>
#include <utils/algorithm.h>

sabers::sabers(std::uint32_t entity_id) : entity_id(entity_id) {}

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
	if (has_value(targets_, target_index))
	{
		if (used)
			return;

		for (auto targeted_index : targets_)
			use(targeted_index);
		use(target_index);

		used = true;

	} else {
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

	sender::send(make_action_message("sabers", entity_id, index_on));

	damage_dealers::standard_damage_dealer(melee_damage(damage, game_board().at(index_on), entity_id));
}
