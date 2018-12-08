#pragma once

#include <external/json.hpp>
#include <core/game_state.h>

template <typename K, typename T>
void json_to_unordered_map(const nlohmann::json& j, std::unordered_map<K, T>& x) {
	std::vector<std::pair<K, T>> values = j;
	for (auto&& pack : values) {
		x.emplace(pack);
	}
}

namespace states {

inline void to_json(nlohmann::json& j, const target_types& x) {
	static std::unordered_map<target_types, std::string, target_types_key_hash> converter = {
			{target_types::caster, "caster"},
			{target_types::enemy, "enemy"},
			{target_types::friendly, "friendly"},
			{target_types::neutral, "neutral"},
			{target_types::moving, "moving"},
			{target_types::all, "all"},
			{target_types::non, "non"}
	};
	j = converter.at(x);
}

inline void from_json(const nlohmann::json& j, target_types& x) {
	//x = static_cast<target_types>(j.get<std::int32_t>());
	std::string target_type = j.get<std::string>();
	static std::unordered_map<std::string, target_types> converter = {
			{"caster", target_types::caster},
			{"enemy", target_types::enemy},
			{"friendly", target_types::friendly},
			{"neutral", target_types::neutral},
			{"moving", target_types::moving},
			{"all", target_types::all},
			{"non", target_types::non}
	};
	x = converter.at(target_type);
}

inline void to_json(nlohmann::json& j, const states_types& x) {
	j = static_cast<std::int32_t>(x);
}

inline void from_json(const nlohmann::json& j, states_types& x) {
	x = static_cast<states_types>(j.get<std::int32_t>());
}

}

inline void to_json(nlohmann::json& j, const global_game_state& x) {
	j = nlohmann::json{
			{"board", x.board.fields_},
			{"healths", x.healths},
			{"entities_names", x.entities_names},
			{"entities_additional_effects", x.entities_additional_effects}
	};
}

inline void from_json(const nlohmann::json& j, global_game_state& x) {
	x.board.fields_ = j.at("board").get<decltype(x.board.fields_)>();
	json_to_unordered_map(j.at("healths"), x.healths);
	json_to_unordered_map(j.at("entities_names"), x.entities_names);
	json_to_unordered_map(j.at("entities_additional_effects"), x.entities_additional_effects);
}

inline void to_json(nlohmann::json& j, const local_game_state& x) {

    static std::unordered_map<target_types, std::string, target_types_key_hash> converter = {
            {target_types::caster, "caster"},
            {target_types::enemy, "enemy"},
            {target_types::friendly, "friendly"},
            {target_types::neutral, "neutral"},
            {target_types::moving, "moving"},
            {target_types::all, "all"},
            {target_types::non, "non"}
    };
	j = nlohmann::json{
			{"possible_movements", x.possible_movements},
			{"valid_movements", x.valid_movements},
			{"selected_index", x.selected_index},
			{"actual_target_type", converter.at(x.actual_target_type)},
			{"button_bitmaps", x.button_bitmaps},
			{"entity_name", x.entity_name}
	};
}

inline void from_json(const nlohmann::json& j, local_game_state& x) {

    static std::unordered_map<std::string, target_types> converter = {
            {"caster", target_types::caster},
            {"enemy", target_types::enemy},
            {"friendly", target_types::friendly},
            {"neutral", target_types::neutral},
            {"moving", target_types::moving},
            {"all", target_types::all},
            {"non", target_types::non}
    };

    x.possible_movements = j.at("possible_movements").get<decltype(x.possible_movements)>();
    x.valid_movements = j.at("valid_movements").get<decltype(x.valid_movements)>();
    x.selected_index = j.at("selected_index");
    std::string temp = j.at("actual_target_type");
    x.actual_target_type = converter.at(temp);
	x.button_bitmaps = j.at("button_bitmaps");
	x.entity_name = j.at("entity_name");
}
