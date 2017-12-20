#ifndef ENTITY_H
#define ENTITY_H

#include <limits>
#include "server/abilities/abilities.h"
#include "server/managers/health_manager.h"
#include "server/managers/power_manager.h"
#include "server/managers/names_manager.h"
#include "server/managers/bitmap_field_manager.h"
#include <tuple>
#include <common/bitmap_field.h>

enum class directions { right, left };

using base_components = std::tuple<name_field, health_field, abilities, directions, bitmap_field>;

template <typename Components>
name_field& entity_name(Components& components) {
	return std::get<name_field>(components);
}

template <typename Components>
health_field& entity_health(Components& components) {
	return std::get<health_field>(components);
}

template <typename Components>
abilities& entity_abilities(Components& components) {
	return std::get<abilities>(components);
}

template <typename Components>
directions& entity_directions(Components& components) {
	return std::get<directions>(components);
}

//template <typename Components>
//drawable::ptr_type& entity_drawer_ptr(Components& components) {
//	return std::get<drawable::ptr_type>(components);
//}

template <typename Components>
bitmap_field& entity_bitmap_field(Components& components) {
	return std::get<bitmap_field>(components);
}

template <typename Components>
power_field& entity_power(Components& components) {
	return std::get<power_field>(components);
}

#endif