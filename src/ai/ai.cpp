#include "ai.h"
#include "abilities/ability.h"
#include "managers/players_manager.h"
#include "core/board.h"
#include "core/states_controller.h"
#include "core/path_finder.h"
#include "abilities/abilities.h"
#include <random>
#include <thread>
#include <chrono>
#include <algorithm>
#include <managers/entity_manager.h>

namespace ai
{
ai_brain::ai_brain(std::uint32_t player_id)
		: player_id(player_id)
{
}

void ai_brain::do_turn()
{
	std::vector<std::uint32_t> entities_indexies;
	players_funcs::player_entities_indexes(player_id, entities_indexies);

	for (auto& entity_index : entities_indexies)
		move_entity(entity_index);
}

void ai_brain::move_entity(std::uint32_t entity_index)
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

	std::vector<std::uint32_t> enemies_indexes;
	players_funcs::enemy_entities_indexes(blackboard.player_id, enemies_indexes);
	if (enemies_indexes.size() == 0)
		return false;

	path_finder distance_finder(true);
	distance_finder.calc(blackboard.my_entity_index_);

	std::vector<std::uint32_t> distances_to_enemies;
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
	auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();
	auto offensive = abilities_ptr->of_type(ability_types::offensive);
	if (!offensive)
		return false;

	try_prepare_ability(*offensive, states::state_controller::selected_index_);
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
	auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();
	auto moving = abilities_ptr->of_type(ability_types::moving);
	if (!moving)
		return false;

	path_finder distance_finder(false);
	distance_finder.calc(blackboard.my_entity_index_);

	std::vector<std::uint32_t> neighbors;
	board_helper::neighboring_fields(blackboard.nearest_enemy_index,
									 neighbors, false);

	neighbors.erase(std::remove_if(std::begin(neighbors), std::end(neighbors), [&blackboard](std::uint32_t index) {
		return !board::empty(index) && index != blackboard.my_entity_index_;
	}), std::end(neighbors));

	auto nearest_field = *std::min_element(std::begin(neighbors), std::end(neighbors),
										   [&distance_finder](std::uint32_t first_elem, std::uint32_t second_elem)
										   {
											   return distance_finder.distance_to(first_elem) < distance_finder.distance_to(second_elem);
										   });

	if (nearest_field == blackboard.my_entity_index_)
		return true;

	std::vector<std::uint32_t> path;
	distance_finder.path_to(nearest_field, path);

	try_prepare_ability(*moving, blackboard.my_entity_index_);
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

	auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();
	auto moving = abilities_ptr->of_type(ability_types::moving);
	if (!moving)
		return false;

	if (blackboard.destination_index == blackboard.my_entity_index_)
		return true;

	path_finder path_finder(false);
	path_finder.calc(blackboard.my_entity_index_);

	std::vector<std::uint32_t> path;
	path_finder.path_to(blackboard.destination_index, path);

	try_prepare_ability(*moving, blackboard.my_entity_index_);

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

	auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();
	auto moving = abilities_ptr->of_type(ability_types::moving);
	if (!moving)
		return false;

	if (blackboard.destination_index == blackboard.my_entity_index_)
		return true;

	try_prepare_ability(*moving, blackboard.my_entity_index_);

	return states::state_controller::is_possible_movement(blackboard.destination_index);
}

bool find_position_for_shot::operator()(blackboard& blackboard)
{
	auto selected_index = states::state_controller::selected_index_;
	auto entity_id = board::at(selected_index);
	auto abilities_ptr = entity_manager::get(entity_id).get<abilities>();
	auto offensive = abilities_ptr->of_type(ability_types::offensive);
	if (!offensive)
		return false;

	path_finder path_finder(false);

	auto destination_index = path_finder.find_first_satisfy_conditions(selected_index,
																	   [&offensive, &blackboard](std::uint32_t index)->bool
																	   {
																		   try_prepare_ability(*offensive, index);
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

	std::vector<std::uint32_t> enemies_indexes;
	players_funcs::enemy_entities_indexes(blackboard.player_id, enemies_indexes);
	if (enemies_indexes.empty())
		return false;

	std::int32_t min_health = std::numeric_limits<std::int32_t>::max();
	std::uint32_t min_health_enemy_id = 0;

	for (auto&& enemy_id : enemies_indexes) {
		auto health = entity_manager::get(enemy_id).get<health_field>()->health;

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