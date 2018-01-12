#include "ai.h"
#include "server/abilities/ability.h"
#include "managers/players_manager.h"
#include "core/board.h"
#include "core/states_controller.h"
#include "core/path_finder.h"
#include "server/abilities/abilities.h"
#include <random>
#include <thread>
#include <chrono>
#include <algorithm>
#include <managers/health_manager.h>
#include "server/managers/abilities_manager.h"

namespace ai
{
ai_brain::ai_brain(sf::Uint64 player_id)
		: player_id(player_id)
{
}

void ai_brain::do_turn()
{
	std::vector<sf::Uint64> entities_indexies;
	players_funcs::player_entities_indexes(player_id, entities_indexies);

	for (auto& entity_index : entities_indexies)
		move_entity(entity_index);
}

void ai_brain::move_entity(sf::Uint64 entity_index)
{
	states::state_controller::selected_index_ = entity_index;

	using namespace behavior_tree_tasks;

	//auto ai_selector = std::make_shared<behavior_tree::selector<blackboard>>();
	//ai_selector->add_task(make_task<attack_enemy>());

	//auto go_end_attack_sequence = std::make_shared<behavior_tree::sequence<blackboard>>();
	//go_end_attack_sequence->add_task(make_task<find_position_for_shot>());
	//go_end_attack_sequence->add_task(make_task<go_to>());

	//go_end_attack_sequence->add_task(make_task<go_close_to>());
	//go_end_attack_sequence->add_task(make_task<attack_enemy>());

	//ai_selector->add_task(go_end_attack_sequence);

	//behavior_tree::sequence<blackboard> ai_sequence;

	//ai_sequence.add_task(make_task<find_nearest_enemy>());
	//ai_sequence.add_task(make_task<attack_enemy>());

	auto ai_sequence = behavior_tree::helper::Sequence<blackboard, find_nearest_enemy, attack_enemy>::create();

	blackboard blackboard_data(player_id, entity_index);
	auto result = (*ai_sequence)(blackboard_data);
}

namespace behavior_tree_tasks
{
using namespace behavior_tree;

bool find_nearest_enemy::operator()(blackboard& blackboard)
{

	std::cout << "blackboard.player_id: " << blackboard.player_id << "\n";

	std::vector<sf::Uint64> enemies_indexes;
	players_funcs::enemy_entities_indexes(blackboard.player_id, enemies_indexes);
	if (enemies_indexes.size() == 0)
		return false;

	path_finder distance_finder(true);
	distance_finder.calc(blackboard.my_entity_index_);

	std::vector<sf::Uint64> distances_to_enemies;
	for (auto& enemy_index : enemies_indexes)
		distances_to_enemies.push_back(distance_finder.distance_to(enemy_index));

	auto min_it = std::min_element(std::begin(distances_to_enemies),
								   std::end(distances_to_enemies));

	blackboard.nearest_enemy_index = enemies_indexes[min_it - std::begin(distances_to_enemies)];

	std::cout << "nearest_enemy_index: " << blackboard.nearest_enemy_index << "\n";

	return true;
}

bool attack_enemy::operator()(blackboard& blackboard)
{
	auto selected_index = states::state_controller::selected_index_;
	auto entity_id = board::at(selected_index);
	auto& entity_abilities = abilities_manager::component_for(entity_id);
	auto offensive = entity_abilities.type(abilities::ability_types::offensive);
	if (!offensive)
		return false;

	(*offensive)(states::state_controller::selected_index_);
	auto can_attack = states::state_controller::is_possible_movement(blackboard.nearest_enemy_index);
	if (can_attack) {
		states::state_controller::do_action(blackboard.nearest_enemy_index);
		std::cout << "can_attack\n";
	}


	std::cout << "attack_enemy\n";

	return can_attack;
}

bool go_close_to::operator()(blackboard& blackboard)
{
	auto entity_id = board::at(blackboard.my_entity_index_);
	auto& entity_abilities = abilities_manager::component_for(entity_id);
	auto moving = entity_abilities.type(abilities::ability_types::moving);
	if (!moving)
		return false;

	path_finder distance_finder(false);
	distance_finder.calc(blackboard.my_entity_index_);

	std::vector<sf::Uint64> neighbors;
	board_helper::neighboring_fields(blackboard.nearest_enemy_index,
									 neighbors, false);

	neighbors.erase(std::remove_if(std::begin(neighbors), std::end(neighbors), [&blackboard](sf::Uint64 index) {
		return !board::empty(index) && index != blackboard.my_entity_index_;
	}), std::end(neighbors));

	auto nearest_field = *std::min_element(std::begin(neighbors), std::end(neighbors),
										   [&distance_finder](sf::Uint64 first_elem, sf::Uint64 second_elem)
										   {
											   return distance_finder.distance_to(first_elem) < distance_finder.distance_to(second_elem);
										   });

	if (nearest_field == blackboard.my_entity_index_)
		return true;

	std::vector<sf::Uint64> path;
	distance_finder.path_to(nearest_field, path);

	(*moving)(blackboard.my_entity_index_);
	for (auto& step : path)
	{
		if (states::state_controller::is_possible_movement(step))
		{
			states::state_controller::do_action(step);
			return true;
		}
	}
	return false;
}

bool go_to::operator()(blackboard& blackboard)
{
	auto entity_id = board::at(blackboard.my_entity_index_);

	auto& entity_abilities = abilities_manager::component_for(entity_id);
	auto moving = entity_abilities.type(abilities::ability_types::moving);
	if (!moving)
		return false;

	if (blackboard.destination_index == blackboard.my_entity_index_)
		return true;

	path_finder path_finder(false);
	path_finder.calc(blackboard.my_entity_index_);

	std::vector<sf::Uint64> path;
	path_finder.path_to(blackboard.destination_index, path);

	(*moving)(blackboard.my_entity_index_);

	for (auto& step : path)
	{
		if (states::state_controller::is_possible_movement(step))
		{
			states::state_controller::do_action(step);
			return true;
		}
	}
	return false;
}

bool can_go_to::operator()(blackboard& blackboard)
{
	auto entity_id = board::at(blackboard.my_entity_index_);

	auto& entity_abilities = abilities_manager::component_for(entity_id);
	auto moving = entity_abilities.type(abilities::ability_types::moving);
	if (!moving)
		return false;

	if (blackboard.destination_index == blackboard.my_entity_index_)
		return true;

	(*moving)(blackboard.my_entity_index_);

	return states::state_controller::is_possible_movement(blackboard.destination_index);
}

bool find_position_for_shot::operator()(blackboard& blackboard)
{
	auto selected_index = states::state_controller::selected_index_;
	auto entity_id = board::at(selected_index);
	auto& entity_abilities = abilities_manager::component_for(entity_id);
	auto offensive = entity_abilities.type(abilities::ability_types::offensive);
	if (!offensive)
		return false;

	path_finder path_finder(false);

	auto destination_index = path_finder.find_first_satisfy_conditions(selected_index,
																	   [&offensive, &blackboard](sf::Uint64 index)->bool
																	   {
																		   (*offensive)(index);
																		   auto can_attack =
																				   states::state_controller::is_possible_movement(blackboard.nearest_enemy_index);
																		   if (can_attack)
																			   return true;
																		   return false;
																	   });
	blackboard.destination_index = destination_index;
	if (destination_index != -1)
		return true;
	return false;
}

bool find_best_aim::operator()(blackboard& blackboard) {

	std::vector<sf::Uint64> enemies_indexes;
	players_funcs::enemy_entities_indexes(blackboard.player_id, enemies_indexes);
	if (enemies_indexes.size() == 0)
		return false;

	sf::Int32 min_health = std::numeric_limits<sf::Int32>::max();
	sf::Uint64 min_health_enemy_id = 0;

	for (auto&& enemy_id : enemies_indexes) {
		auto health = healths_manager::component_for(enemy_id).health;
		if (health < min_health) {
			min_health = health;
			min_health_enemy_id = enemy_id;
		}
	}

	blackboard.nearest_enemy_index = min_health_enemy_id;

	return true;
}

}
};