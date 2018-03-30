#ifndef STATES_CONTROLLER_H
#define STATES_CONTROLLER_H

#include <utility>
#include <vector>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include "path_finder.h"
#include "states.h"

namespace states
{

class state_controller
{
public:
	static void wait_for_action(const std::function<void(std::uint32_t index)>& caller);
	static void do_action(std::uint32_t index);
	static bool is_possible_movement(std::uint32_t index);
	static void first_state(std::uint32_t select_from_index);
	static bool valid_target(std::uint32_t target_index);

	static std::uint32_t selected_index_;
	static states_types actual_state_;
	static target_types actual_targeting_type_;
	static std::vector<std::uint32_t> possible_movements_;
	static std::vector<std::uint32_t> possible_movements_costs_;

	static std::function<void(std::uint32_t)> caller_;

	static std::unordered_map<std::uint32_t, std::unordered_set<std::uint32_t>> custom_valid_targets;

	enum class custom_target_type {
		board_index,
		entity_id
	};

	static custom_target_type custom_valid_target_type;
};

};

#endif