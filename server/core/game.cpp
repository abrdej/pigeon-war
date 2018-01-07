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
#include "gui/effects_manager.h"
#include "ai/ai_manager.h"
#include "scenarios/scenarios.h"
#include "utils/scenario_helper.h"
#include <iostream>

game::game() {
	create_scenario(*this, "saurions_web");
}

void game::initialize(std::array<std::vector<std::size_t>, board::cols_n * board::rows_n>& x) {
	x = board::fields_;
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

void game::on_board_2(std::size_t col, std::size_t row, local_state& lstate) {

	using namespace states;

	auto index = board::to_index(col, row);

	if (board::empty(index) && state_controller::actual_state_ == states_types::waiting)
		return;

	if (!board::empty(index)) {

		lstate.selected_index = index;

		auto entity_id = board::at(index);
		auto& entity_abilities = abilities_manager::component_for(entity_id);

		auto bkpm = state_controller::possible_movements_;
		auto bkatt = state_controller::actual_targeting_type_;

		if (entity_abilities.is_active) {
			auto moveable = entity_abilities.at(0);
			if (moveable) {
				moveable->operator()(index);
			}
		}

		lstate.possible_movements = state_controller::possible_movements_;
		lstate.actual_target_type = state_controller::actual_targeting_type_;

		lstate.button_bitmaps.fill(bitmap_key::none);

		auto id = board::at(index);
		if (id != board::empty_id) {
			auto& bitmap_field = bitmap_field_manager::component_for(id);
			lstate.button_bitmaps[0] = bitmap_field.bmt_key;

			auto& abilities = abilities_manager::component_for(board::at(index));
			for (std::size_t i = 1; i < 6; ++i) {
				auto ability = abilities.at(i - 1);
				if (ability) {
					lstate.button_bitmaps[i] = ability->get_bitmap_key();
				}
			}
		}

		lstate.entity_name = names_manager::component_for(board::at(index));

		state_controller::possible_movements_ = bkpm;
		state_controller::actual_targeting_type_ = bkatt;
	}
}

void game::on_button(size_t n)
{
	if (n >= 0 && n <= 3) // 4 is passive
	{
		auto selected_index = states::state_controller::selected_index_;

		if (!players_funcs::player_entity(selected_index)) {
			std::cout << "not player entity\n";
			return;
		}

		auto entity_id = board::at(selected_index);
		auto& entity_abilities = abilities_manager::component_for(entity_id);

		if (entity_abilities.is_active) {
			auto entity_ability = entity_abilities.at(n);
			if (entity_ability) {
				entity_ability->operator()(states::state_controller::selected_index_);
			}
		}
	}
	if (n == 5)
	{
		turn::turn_system::end_turn();
		players::next_player();

		states::state_controller::first_state(players_funcs::active_player_first_entity_index());

		if (players::active_player_ai())
		{
			ai_manager::perform_movement();
			turn::turn_system::end_turn();
			players::next_player();
			states::state_controller::first_state(players_funcs::active_player_first_entity_index());
			//on_button(14);
		}
	}
}

void game::on_button_2(std::size_t n, local_state& lstate) {

	if (n >= 0 && n <= 3) // 4 is passive
	{
		auto selected_index = lstate.selected_index;

		//if (!players_funcs::player_entity(selected_index)) {
		//	std::cout << "not player entity\n";
		//	return;
		//}

		auto entity_id = board::at(selected_index);
		auto& entity_abilities = abilities_manager::component_for(entity_id);

		auto bkpm = states::state_controller::possible_movements_;
		auto bkatt = states::state_controller::actual_targeting_type_;

		if (entity_abilities.is_active) {
			auto entity_ability = entity_abilities.at(n);
			if (entity_ability) {
				entity_ability->operator()(states::state_controller::selected_index_);
			}
		}

		lstate.possible_movements = states::state_controller::possible_movements_;
		lstate.actual_target_type = states::state_controller::actual_targeting_type_;

		states::state_controller::possible_movements_ = bkpm;
		states::state_controller::actual_targeting_type_ = bkatt;

	}
}

bool game::valid_target(size_t target_index) const
{
	if (states::state_controller::actual_targeting_type_ == states::target_types::enemy) {

		auto caster_id = board::at(states::state_controller::selected_index_);
		auto target_id = board::at(target_index);

		if (!states::state_controller::custom_valid_targets[caster_id].empty()) {
			return states::state_controller::custom_valid_targets[caster_id].find(target_id) !=
				   std::end(states::state_controller::custom_valid_targets[caster_id]);
		}

		return players_funcs::enemy_entity(target_index);
	}
	else if (states::state_controller::actual_targeting_type_ == states::target_types::moving)
		return board::empty(target_index);
	else if (states::state_controller::actual_targeting_type_ == states::target_types::friendly)
		return players_funcs::player_entity(target_index);
	else if (states::state_controller::actual_targeting_type_ == states::target_types::caster)
		return target_index == states::state_controller::selected_index_;
	else if (states::state_controller::actual_targeting_type_ == states::target_types::neutral) {
        std::cout << "neutral: " << players_funcs::neutral_entity(target_index) << "\n";
        return players_funcs::neutral_entity(target_index);
    } else if (states::state_controller::actual_targeting_type_ == states::target_types::all) {
        return true;
    }
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

	animations_queue::push_animation(animation_types::flash_bitmap,
									 board::to_index(13, 5),
									 100,
									 0,
									 bitmap_key::hello);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 board::to_index(13, 4),
									 100,
									 0,
									 bitmap_key::hello);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 board::to_index(13, 3),
									 100,
									 0,
									 bitmap_key::hello);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 board::to_index(13, 6),
									 100,
									 0,
									 bitmap_key::hello);

	animations_queue::push_animation(animation_types::flash_bitmap,
									 board::to_index(13, 7),
									 100,
									 0,
									 bitmap_key::hello);

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