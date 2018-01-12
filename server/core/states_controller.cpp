#include "states_controller.h"
#include "common/states.h"
#include "board.h"
#include "managers/entity_manager.h"
#include "abilities/abilities.h"
#include "abilities/ability.h"
#include "managers/abilities_manager.h"

using states::state_controller;
using states::states_types;
using states::target_types;

sf::Uint64 state_controller::selected_index_ = states::no_selected_index;
states_types state_controller::actual_state_ = states_types::waiting;
target_types state_controller::actual_targeting_type_ = target_types::non;

std::vector<sf::Uint64> state_controller::possible_movements_;
std::vector<sf::Uint64> state_controller::possible_movements_costs_;

std::function<void(sf::Uint64)> state_controller::caller_;

std::unordered_map<sf::Uint64, std::unordered_set<sf::Uint64>> state_controller::custom_valid_targets;

state_controller::custom_target_type state_controller::custom_valid_target_type = state_controller::custom_target_type::board_index;

void state_controller::first_state(sf::Uint64 select_from_index)
{
	if (select_from_index == no_selected_index)
		return;

	selected_index_ = select_from_index;
	sf::Uint64 selected_index = states::state_controller::selected_index_;
	auto entity_id = board::at(selected_index);
	auto& entity_abilities = abilities_manager::component_for(entity_id);

	if (entity_abilities.is_active) {
		auto moveable = entity_abilities.at(0);
		if (moveable) {
			moveable->operator()(states::state_controller::selected_index_);
		}
	}
}

void state_controller::wait_for_action(const std::function<void(sf::Uint64 index)>& caller)
{
	state_controller::actual_state_ = states_types::wait_for_action;
	caller_ = caller;
}

void state_controller::do_action(sf::Uint64 index)
{
	caller_(index);
}

bool state_controller::is_possible_movement(sf::Uint64 index)
{
	auto begin_it = std::begin(states::state_controller::possible_movements_);
	auto end_it = std::end(states::state_controller::possible_movements_);
	auto result = std::find(begin_it, end_it, index);
	return result != end_it;
}

bool state_controller::valid_target(sf::Uint64 target_index) {

	if (states::state_controller::actual_targeting_type_ == states::target_types::enemy) {

		auto caster_id = board::at(states::state_controller::selected_index_);

		sf::Uint64 target_value = target_index;

		if (custom_valid_target_type == custom_target_type::entity_id)
			target_value = board::at(target_index);

		if (!states::state_controller::custom_valid_targets[caster_id].empty()) {

			std::cout << "custom\n";

			return states::state_controller::custom_valid_targets[caster_id].find(target_value) !=
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