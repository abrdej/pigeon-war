#include "game.h"
#include "core/path_finder.h"
#include "abilities/moveable.h"
#include "abilities/abilities.h"
#include "states.h"
#include "abilities/ability.h"
#include "ai/ai.h"
#include "entities/werewolf.h"
#include "animation/animation.h"
#include "entities/stone.h"
#include "entities/saurian.h"
#include "entities/saberhand.h"
#include "utils/creator_helper.h"
#include "entities/wolf.h"
#include "entities/saurions_web.h"
#include "entities/native.h"
#include "abilities/damage_dealers.h"
#include "abilities/drain.h"
#include "gui/effects_manager.h"
#include "ai/ai_manager.h"
#include "scenarios/scenarios.h"
#include "utils/scenario_helper.h"
#include <iostream>

game::game() {
	create_scenario(*this, "saurions_web");
}

void game::on_board(size_t col, size_t row)
{
	using namespace states;

	auto index = board::to_index(col, row);
	if (board::empty(index) && state_controller::actual_state_ == states_types::waiting)
		return;

	else if (state_controller::actual_state_ == states_types::wait_for_action)
	{
		if (state_controller::is_possible_movement(index) && valid_target(index))
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

void game::on_button(size_t n)
{
	if (n >= 0 && n <= 5)
	{
		auto selected_index = states::state_controller::selected_index_;

		if (!players_funcs::player_entity(selected_index)) {
			std::cout << "not player entity\n";
			return;
		}

		auto entity_id = board::at(selected_index);
		auto& entity_abilities = abilities_manager::component_for(entity_id);
		auto entity_ability = entity_abilities.at(n);
		if (entity_ability) {
			entity_ability->operator()(states::state_controller::selected_index_);
		}
	}
	if (n == 14)
	{
		turn::turn_system::end_turn();
		players::next_player();

		states::state_controller::first_state(players_funcs::active_player_first_entity_index());

		if (players::active_player_ai())
		{
			ai_manager::perform_movement();
			turn::turn_system::end_turn();
			//players::next_player();
			//states::state_controller::first_state(players_funcs::active_player_first_entity_index());
			on_button(14);
		}
	}
}

bool game::valid_target(size_t target_index) const
{
	if (states::state_controller::actual_targeting_type_ == states::target_types::enemy)
		return players_funcs::enemy_entity(target_index);
	else if (states::state_controller::actual_targeting_type_ == states::target_types::moving)
		return board::empty(target_index);
	else if (states::state_controller::actual_targeting_type_ == states::target_types::friendly)
		return players_funcs::player_entity(target_index);
	else if (states::state_controller::actual_targeting_type_ == states::target_types::caster)
		return target_index == states::state_controller::selected_index_;
	return false;
}

void game::defeat() {
    std::exit(0);
}

void game::victory() {
    std::exit(0);
}

void game::create_werewolf()
{
	size_t wolf1_id = entity_manager::create<wolf>();
	size_t wolf2_id = entity_manager::create<wolf>();
	size_t wolf3_id = entity_manager::create<wolf>();
	size_t wolf4_id = entity_manager::create<wolf>();

	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(13, 5), std::chrono::milliseconds(100), "hello.png"));
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(13, 4), std::chrono::milliseconds(100), "hello.png"));
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(13, 3), std::chrono::milliseconds(100), "hello.png"));
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(13, 6), std::chrono::milliseconds(100), "hello.png"));
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(board::to_index(13, 7), std::chrono::milliseconds(100), "hello.png"));
	animation::base_player::play();

	//board_.insert(board::to_index(13, 5), beast);
	board::insert(board::to_index(13, 4), wolf1_id);
	board::insert(board::to_index(13, 3), wolf2_id);
	board::insert(board::to_index(13, 6), wolf3_id);
	board::insert(board::to_index(13, 7), wolf4_id);

	//players::add_entity_for_player(L"enemy", beast);
	players::add_entity_for_player("enemy", wolf1_id);
	players::add_entity_for_player("enemy", wolf2_id);
	players::add_entity_for_player("enemy", wolf3_id);
	players::add_entity_for_player("enemy", wolf4_id);
}