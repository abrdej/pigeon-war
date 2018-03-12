//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_COMMON_DATA_H
#define PIGEONWAR_COMMON_DATA_H

#include "client/board_container.h"
#include "common/states.h"
#include "common/bitmaps.h"
#include <unordered_set>
#include <unordered_map>
#include "json.hpp"

static const auto no_selection = std::numeric_limits<std::uint32_t>::max();

struct game_state {
	board_container board;
	std::unordered_map<std::uint32_t, std::int32_t> healths;
	std::unordered_map<std::uint32_t, std::string> entities_names;
	std::unordered_map<std::uint32_t, std::vector<std::string>> entities_additional_effects;
};

struct local_state {
	std::vector<std::uint32_t> possible_movements;
	std::unordered_set<std::uint32_t> valid_movements;
	std::uint32_t selected_index{no_selection};
	target_types actual_target_type{target_types::non};
	std::array<std::string, 5> button_bitmaps;
	std::string entity_name;
};

#endif //PIGEONWAR_COMMON_DATA_H
