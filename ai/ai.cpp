#include "ai.h"

#include "core/players.h"
#include "core/board.h"
#include "core/states.h"
#include "core/path_finder.h"
#include "abilities/abilities.h"
#include <random>
#include <thread>
#include <chrono>
#include <algorithm>
#include "managers/abilities_manager.h"

namespace ai
{
	ai_brain::ai_brain(const players::player_id_type& player_name)
		: player_name_(player_name)
	{
	}

	void ai_brain::do_turn()
	{
		std::vector<size_t> entities_indexies;
        players_funcs::player_entities_indexes(player_name_, entities_indexies);

		for (auto& entity_index : entities_indexies)
			move_entity(entity_index);
	}

	void ai_brain::move_entity(size_t entity_index)
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

		blackboard blackboard_data(player_name_, entity_index);
		auto result = (*ai_sequence)(blackboard_data);
	}

	namespace behavior_tree_tasks
	{
		using namespace behavior_tree;

		bool find_nearest_enemy::operator()(blackboard& blackboard)
		{
			std::vector<size_t> enemies_indexies;
			players_funcs::enemy_entities_indexes(blackboard.player_name_, enemies_indexies);
			if (enemies_indexies.size() == 0)
				return false;

			path_finder distance_finder(true);
			distance_finder.calc(blackboard.my_entity_index_);

			std::vector<size_t> distances_to_enemies;
			for (auto& enemy_index : enemies_indexies)
				distances_to_enemies.push_back(distance_finder.distance_to(enemy_index));

			auto min_it = std::min_element(std::begin(distances_to_enemies),
				std::end(distances_to_enemies));

			blackboard.nearest_enemy_index = enemies_indexies[min_it - std::begin(distances_to_enemies)];

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
			if (can_attack)
				states::state_controller::do_action(blackboard.nearest_enemy_index);
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

			std::vector<size_t> neighbors;
			board_helper::neighboring_fields(blackboard.nearest_enemy_index,
				neighbors, true);

			auto nearest_field = *std::min_element(std::begin(neighbors), std::end(neighbors),
				[&distance_finder](size_t first_elem, size_t second_elem)
			{
				return distance_finder.distance_to(first_elem) < distance_finder.distance_to(second_elem);
			});

			std::vector<size_t> path;
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
			//if (!abilities_manager::moving::has(entity_id))
			//	return false;

			auto& entity_abilities = abilities_manager::component_for(entity_id);
			auto moving = entity_abilities.type(abilities::ability_types::moving);
			if (!moving)
				return false;

			path_finder path_finder(false);
			path_finder.calc(blackboard.my_entity_index_);

			std::vector<size_t> path;
			path_finder.path_to(blackboard.destination_index, path);

			(*moving)(blackboard.my_entity_index_);
			//abilities_manager::moving::init(entity_id, blackboard.my_entity_index_);
			// moving_manager::init(entity_id, index_for);
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
				[&offensive, &blackboard](size_t index)->bool
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
	}
};