#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <core/game.h>
#include <core/path_finder.h>
#include <core/states.h>

class game_controller {
    std::function<void(std::uint32_t)> action_;

public:
	void on_board(std::uint32_t col, std::uint32_t row);
	void on_button(std::uint32_t n);
	void defeat();
	void victory(std::uint32_t player_id);
	void wait_for_action(const std::function<void(std::uint32_t index)>& caller);
	void do_action(std::uint32_t index);
	bool is_possible_movement(std::uint32_t index);
	void set_entity_default_state(std::uint32_t select_from_index);
	bool valid_target(std::uint32_t target_index);

	std::uint32_t selected_index_{no_selected_index};
	states_types actual_state_{states_types::waiting};
	target_types actual_targeting_type_{target_types::non};
	std::vector<std::uint32_t> possible_movements_;
	std::vector<std::uint32_t> possible_movements_costs_;

	std::unordered_map<std::uint32_t, std::unordered_set<std::uint32_t>> custom_valid_targets;

	enum class custom_target_type {
		board_index,
		entity_id
	};

	custom_target_type custom_valid_target_type{custom_target_type::board_index};
};

inline auto& game_control() {
    return game::get<game_controller>();
}
