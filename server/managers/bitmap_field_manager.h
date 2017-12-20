//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_BITMAP_FIELD_MANAGER_H
#define PIGEONWAR_BITMAP_FIELD_MANAGER_H

#include "common/managers.h"
#include "common/bitmap_field.h"

struct bitmap_field_manager : base_manager<bitmap_field, bitmap_field&>
{
	static std::unordered_map<std::size_t, bitmap_key> get_map() {
		std::unordered_map<std::size_t, bitmap_key> returned_map;

		for (auto&& elem : map_) {
			returned_map.insert(std::make_pair(elem.first, elem.second.bmt_key));
		}

		return std::move(returned_map);
	}
};

template <>
inline void add_component_of_type<bitmap_field>(std::size_t entity_id, const bitmap_field& component) {
	bitmap_field_manager::add_component(entity_id, component);
}

#endif //PIGEONWAR_BITMAP_FIELD_MANAGER_H
