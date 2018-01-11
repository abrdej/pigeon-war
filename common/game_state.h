//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_COMMON_DATA_H
#define PIGEONWAR_COMMON_DATA_H

#include "client/board_container.h"
#include "common/states.h"
#include "common/bitmaps.h"
#include "animations.h"
#include <unordered_set>
#include <unordered_map>
#include "packet_helper.h"
#include "define_packet.h"

static const auto no_selection = std::numeric_limits<std::size_t>::max();

struct game_state {
	board_container board;
	std::unordered_map<std::size_t, int> healths;
	std::unordered_map<std::size_t, bitmap_key> entities_bitmaps;
	std::unordered_map<std::size_t, std::vector<std::string>> entities_additional_effects;
	std::vector<animation_pack> animations_queue;
};

struct local_state {
	std::vector<std::size_t> possible_movements;
	std::unordered_set<std::size_t> valid_movements;
	std::size_t selected_index{no_selection};
	states::target_types actual_target_type{states::target_types::non};
	std::array<bitmap_key, 6> button_bitmaps;
	std::string entity_name;
};

PACKET_DEFINE4(game_state, board, healths, entities_bitmaps, entities_additional_effects)

PACKET_DEFINE6(local_state, possible_movements, valid_movements, selected_index, actual_target_type,  button_bitmaps, entity_name)

#endif //PIGEONWAR_COMMON_DATA_H
