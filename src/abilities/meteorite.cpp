#include "meteorite.h"
#include <managers/entity_manager.h>
#include <components/power_field.h>
#include <server/sender.h>
#include <components/damage_pack.h>
#include <components/applied_effects.h>
#include <messages/massages_makers.h>
#include "damage_dealers.h"

meteorite::meteorite(std::uint32_t entity_id)
		: entity_id(entity_id) {}

std::string meteorite::hint() const {
	auto power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;
	return "Magic power: " + std::to_string(power);
}

void meteorite::prepare(std::uint32_t for_index) {

	game_control().selected_index_ = for_index;

	board_helper::all(game_control().possible_movements_);

	game_control().actual_targeting_type_ = target_types::all;

	game_control().wait_for_action([this](std::uint32_t index)
											  {
												  game_control().possible_movements_.clear();
												  return use(index);
											  });
}

void meteorite::use(std::uint32_t index_on) {

	if (used)
		return;

	auto& power = game::get<entity_manager>().get(entity_id).get<power_filed>()->power;

	if (power < power_cost)
		return;

	auto used_from_index = game_control().selected_index_;
	auto caster_id = game_board().at(used_from_index);
	auto damage = this->damage;

	sender::send(make_action_message("meteorite_before", index_on));

	meteorite_holder = make_after_n_round_callback_holder(1,
														  [caster_id, index_on, damage]() mutable {

															  sender::send(make_action_message("meteorite", index_on));

															  std::vector<std::uint32_t> neighbors;
															  board_helper::neighboring_fields(index_on, neighbors, false);

															  if (!game_board().empty(index_on)) {
																  damage_dealers::standard_damage_dealer(magic_damage(damage, game_board().at(index_on), caster_id));
															  }

															  for (auto& index : neighbors) {
																  if (!game_board().empty(index))
																	  damage_dealers::standard_damage_dealer(magic_damage(damage, game_board().at(index), caster_id));
															  }
														  });

	power -= power_cost;

	used = true;
}