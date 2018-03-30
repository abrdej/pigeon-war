//
// Created by abrdej on 18.01.18.
//

#ifndef PIGEONWAR_AURAS_OBSERVER_H
#define PIGEONWAR_AURAS_OBSERVER_H

#include <memory>
#include <unordered_map>
#include <vector>
#include <core/board.h>
#include <core/path_finder.h>
#include <managers/entity_manager.h>
#include "base_effect.h"

class auras_observer {

	static std::unique_ptr<auras_observer> impl;

	static auras_observer& get_instance() {
		if (!impl) {
			impl = std::make_unique<auras_observer>();
			board::on_change([]() {
				auras_observer::observe();
			});
		}
		return *impl;
	}

	std::unordered_map<std::uint32_t, std::shared_ptr<effect>> auras;

	std::vector<std::pair<std::uint32_t, std::shared_ptr<effect>>> entities_with_auras;

public:
	static void add_aura(std::uint32_t for_entity, const std::shared_ptr<effect>& aura) {
		get_instance().auras.emplace(for_entity, aura);
	}
	static void remove_aura(std::uint32_t from_entity) {
		get_instance().auras.erase(from_entity);
	}

	static void observe() {

		std::vector<bool> entities_to_remove_aura(get_instance().entities_with_auras.size(), true);

		for (auto&& entity_with_aura_pack : get_instance().entities_with_auras) {
			entity_with_aura_pack.second->remove_effect(entity_with_aura_pack.first);
		}
		get_instance().entities_with_auras.clear();

		std::vector<std::uint32_t> to_remove;

		for (auto&& aura_pack : get_instance().auras) {

			if (entity_manager::alive(aura_pack.first)) {
				auto board_index = board::index_for(aura_pack.first);

				std::vector<std::uint32_t> neighbors;
				board_helper::neighboring_fields(board_index, neighbors, false);

				for (auto&& neighbour_index : neighbors) {
					if (!board::empty(neighbour_index)) {

						auto entity_id = board::at(neighbour_index);
						if (aura_pack.second->set_effect(entity_id)) {
							get_instance().entities_with_auras.emplace_back(board::at(neighbour_index), aura_pack.second);
						}
					}
				}
			} else {
				to_remove.push_back(aura_pack.first);
			}
		}

		for (auto&& entity_id : to_remove) {
			get_instance().auras.erase(entity_id);
		}

	}
};


#endif //PIGEONWAR_AURAS_OBSERVER_H
