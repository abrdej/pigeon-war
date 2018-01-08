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
	static void wait_for_action(const std::function<void(size_t index)>& caller);
	static void do_action(size_t index);
	static bool is_possible_movement(size_t index);
	static void first_state(size_t select_from_index);
	static bool valid_target(std::size_t target_index);

	static size_t selected_index_;
	static states_types actual_state_;
	static target_types actual_targeting_type_;
	static std::vector<size_t> possible_movements_;
	static std::vector<size_t> possible_movements_costs_;

	static std::function<void(std::size_t)> caller_;

	static std::unordered_map<std::size_t, std::unordered_set<std::size_t>> custom_valid_targets;
};

};

#endif