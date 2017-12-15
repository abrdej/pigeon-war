#ifndef ENTITY_H
#define ENTITY_H

#include <limits>
#include "abilities/abilities.h"
#include "managers/health_manager.h"
#include "gui/drawable.h"
#include <tuple>

enum class directions { right, left };

struct name_field {
	std::string value;

	name_field() = default;
	explicit name_field(std::string x) : value(std::move(x)) {}
	operator std::string() {
		return value;
	}
	name_field& operator=(std::string x) {
		this->value = std::move(x);
		return *this;
	}
};

using base_components = std::tuple<name_field, health_field, abilities, directions>;

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

struct entity_definition
{
	explicit entity_definition(const std::type_index& type)
			: type(type) {}
	std::type_index type;
	std::string name;
	health_field health_pack;
	abilities entity_abilities;
	directions direction;
	drawable::ptr_type drawer;
};



namespace entity_helper
{
inline entity_definition turned_right(entity_definition&& data)
{
	data.direction = directions::right;
	return data;
}
inline entity_definition turned_left(entity_definition&& data)
{
	data.direction = directions::left;
	return data;
}
};

#endif