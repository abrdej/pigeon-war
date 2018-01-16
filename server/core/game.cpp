#include "game.h"
#include "path_finder.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "states_controller.h"
#include "abilities/ability.h"
#include "ai/ai.h"
#include "entities/werewolf.h"
#include "entities/stone.h"
#include "entities/saurian.h"
#include "entities/saberhand.h"
#include "utils/creator_helper.h"
#include "entities/wolf.h"
#include "entities/saurions_web.h"
#include "entities/native.h"
#include "abilities/damage_dealers.h"
#include "abilities/drain.h"
#include "ai/ai_manager.h"
#include "scenarios/scenarios.h"
#include "utils/scenario_helper.h"
#include <iostream>

game::game() {
}

void game::initialize(std::array<std::vector<std::uint32_t>, board::cols_n * board::rows_n>& x) {
	x = board::fields_;
}

void game::on_board(std::uint32_t col, std::uint32_t row)
{
	using namespace states;

	auto index = board::to_index(col, row);

	if (board::empty(index) && state_controller::actual_state_ == states_types::waiting)
		return;

	else if (state_controller::actual_state_ == states_types::wait_for_action)
	{
		if (state_controller::is_possible_movement(index) && state_controller::valid_target(index))
			state_controller::do_action(index);

		else if (!board::empty(index) && players_funcs::player_entity(index))
			state_controller::first_state(index);

		else if (!board::empty(index) && !players_funcs::player_entity(index))
		{
			state_controller::actual_state_ = states_types::waiting;
			state_controller::actual_targeting_type_ = target_types::non;
			state_controller::selected_index_ = index;
		}
	}
	else if (!board::empty(index) && players_funcs::player_entity(index))
	{
		state_controller::first_state(index);
	}
	else if (!board::empty(index) && !players_funcs::player_entity(index))
	{
		state_controller::actual_state_ = states_types::waiting;
		state_controller::actual_targeting_type_ = target_types::non;
		state_controller::selected_index_ = index;
	}
}

void game::on_button(std::uint32_t n)
{
	if (n >= 0 && n <= 3) // 4 is passive
	{
		auto selected_index = states::state_controller::selected_index_;

		if (!players_funcs::player_entity(selected_index)) {
			std::cout << "not player entity\n";
			return;
		}

		auto entity_id = board::at(selected_index);
		auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();

		if (abilities_ptr->is_active) {
			auto entity_ability = abilities_ptr->at(n);
			if (entity_ability) {
				entity_ability->operator()(states::state_controller::selected_index_);
			}
		}
	}
	if (n == 5)
	{
		turn::turn_system::end_turn();
		players_manager::next_player();

		states::state_controller::first_state(players_funcs::active_player_first_entity_index());

		if (players_manager::is_active_player_ai())
		{
			ai_manager::perform_movement(players_manager::get_active_player_id());
			turn::turn_system::end_turn();
			players_manager::next_player();
			states::state_controller::first_state(players_funcs::active_player_first_entity_index());
			//on_button(14);
		}
	}
}

std::string game::get_button_description(std::uint32_t selected_index, std::uint32_t n) {

	auto entity_id = board::at(selected_index);
	auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();

	std::string description;

	if (abilities_ptr->is_active) {
		auto entity_ability = abilities_ptr->at(n);
		if (entity_ability) {
			description = entity_ability->hint();
		}
	}

	return std::move(description);
}

void game::defeat() {
    std::exit(0);
}

void game::victory() {
    std::exit(0);
}