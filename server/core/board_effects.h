//
// Created by abrdej on 18.01.18.
//

#ifndef PIGEONWAR_BOARD_EFFECTS_H
#define PIGEONWAR_BOARD_EFFECTS_H

#include <vector>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include "board.h"
#include "effects/base_effect.h"

//class board_effects {
//	static std::unique_ptr<board_effects> impl;
//
//	static board_effects& get_instance() {
//		if (!impl) {
//			impl = std::make_unique<board_effects>();
//		}
//		return *impl;
//	}
//
//	std::array<std::unordered_map<std::uint32_t, std::shared_ptr<effect>>, board::cols_n * board::rows_n> effects;
//
//public:
//	static std::uint32_t put_effect(std::uint32_t board_index, const std::shared_ptr<effect>& x) {
//		static std::uint32_t effect_id_gen = 0;
//		get_instance().effects[board_index].emplace(effect_id_gen, x);
//		return effect_id_gen++;
//	}
//	static void remove_effect(std::uint32_t board_index, std::uint32_t effect_id) {
//		get_instance().effects[board_index].erase(effect_id);
//	}
//	static std::vector<std::shared_ptr<effect>> get_effects(std::uint32_t board_index) {
//		auto& effects = get_instance().effects[board_index];
//		std::vector<std::shared_ptr<effect>> result_effects;
//		for (auto&& effect_pack : effects) {
//			result_effects.push_back(effect_pack.second);
//		}
//		return std::move(result_effects);
//	}
//};


#endif //PIGEONWAR_BOARD_EFFECTS_H
