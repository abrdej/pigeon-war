//
// Created by abrdej on 18.01.18.
//

#ifndef PIGEONWAR_MESSAGES_H
#define PIGEONWAR_MESSAGES_H


#include <common/message_types.h>
#include "common/game_state.h"
#include "json.hpp"

template <typename K, typename T>
void json_to_unordered_map(const nlohmann::json& j, std::unordered_map<K, T>& x) {
	std::vector<std::pair<K, T>> values = j;
	for (auto&& pack : values) {
		x.emplace(pack);
	}
}

namespace states {

inline void to_json(nlohmann::json& j, const target_types& x) {
	j = nlohmann::json{static_cast<std::int32_t>(x)};
}

inline void from_json(const nlohmann::json& j, target_types& x) {
	x = static_cast<target_types>(j.get<std::int32_t>());
}

inline void to_json(nlohmann::json& j, const states_types& x) {
	j = nlohmann::json{static_cast<std::int32_t>(x)};
}

inline void from_json(const nlohmann::json& j, states_types& x) {
	x = static_cast<states_types>(j.get<std::int32_t>());
}

}

inline void to_json(nlohmann::json& j, const bitmap_key& x) {
	j = nlohmann::json{static_cast<std::int32_t>(x)};
}

inline void from_json(const nlohmann::json& j, bitmap_key& x) {
	x = static_cast<bitmap_key>(j.get<std::int32_t>());
}

inline void to_json(nlohmann::json& j, const message_types& x) {
	j = nlohmann::json{static_cast<std::int32_t>(x)};
}

inline void from_json(const nlohmann::json& j, message_types& x) {
	x = static_cast<message_types>(j.get<std::int32_t>());
}

inline void to_json(nlohmann::json& j, const game_state& x) {
	j = nlohmann::json{
			{"board", x.board.fields_},
			{"healths", x.healths},
			{"entities_names", x.entities_names},
			{"entities_additional_effects", x.entities_additional_effects}
	};
}

inline void from_json(const nlohmann::json& j, game_state& x) {
	x.board.fields_ = j.at("board");
	json_to_unordered_map(j.at("healths"), x.healths);
	json_to_unordered_map(j.at("entities_names"), x.entities_names);
	json_to_unordered_map(j.at("entities_additional_effects"), x.entities_additional_effects);
}

inline void to_json(nlohmann::json& j, const local_state& x) {
	j = nlohmann::json{
			{"possible_movements", x.possible_movements},
			{"valid_movements", x.valid_movements},
			{"selected_index", x.selected_index},
			{"actual_target_type", x.actual_target_type},
			{"button_bitmaps", x.button_bitmaps},
			{"entity_name", x.entity_name}
	};
}

void from_json(const nlohmann::json& j, local_state& x) {
	x.possible_movements = j.at("possible_movements").get<decltype(x.possible_movements)>();
	x.valid_movements = j.at("valid_movements").get<decltype(x.valid_movements)>();
	x.selected_index = j.at("selected_index");
	x.actual_target_type = j.at("actual_target_type");
	x.button_bitmaps = j.at("button_bitmaps");
	x.entity_name = j.at("entity_name");
}



#endif //PIGEONWAR_MESSAGES_H
