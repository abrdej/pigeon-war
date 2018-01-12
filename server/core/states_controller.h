#ifndef STATES_CONTROLLER_H
#define STATES_CONTROLLER_H

#include <utility>
#include <vector>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include "path_finder.h"
#include "common/states.h"

namespace states
{

class state_controller
{
public:
	static void wait_for_action(const std::function<void(sf::Uint64 index)>& caller);
	static void do_action(sf::Uint64 index);
	static bool is_possible_movement(sf::Uint64 index);
	static void first_state(sf::Uint64 select_from_index);
	static bool valid_target(sf::Uint64 target_index);

	static sf::Uint64 selected_index_;
	static states_types actual_state_;
	static target_types actual_targeting_type_;
	static std::vector<sf::Uint64> possible_movements_;
	static std::vector<sf::Uint64> possible_movements_costs_;

	static std::function<void(sf::Uint64)> caller_;

	static std::unordered_map<sf::Uint64, std::unordered_set<sf::Uint64>> custom_valid_targets;

	enum class custom_target_type {
		board_index,
		entity_id
	};

	static custom_target_type custom_valid_target_type;
};

};

#endif