#ifndef STATES_H
#define STATES_H

#include <utility>
#include <vector>
#include <functional>
#include "path_finder.h"
//#include "abilities/moveable.h"
//#include "managers/entity_manager.h"
//#include "board.h"

namespace states
{
	enum class states_types { waiting, wait_for_action };
	enum class target_types { caster, enemy, friendly, neutral, moving, all, non };

	static const std::size_t no_selected_index = std::numeric_limits<std::size_t>::max();

	class state_controller
	{
	public:
		static void wait_for_action(const std::function<void(size_t index)>& caller);
		static void do_action(size_t index);
		static bool is_possible_movement(size_t index);
		static void first_state(size_t select_from_index);

		static size_t selected_index_;
		static states_types actual_state_;
		static target_types actual_targeting_type_;
		static std::vector<size_t> possible_movements_;
		static std::vector<size_t> movements_ranges_;
		static std::vector<size_t> possible_movements_costs_;
		static std::function<void(size_t)> caller_;
	};
};

#endif