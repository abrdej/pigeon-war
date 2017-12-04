#ifndef ENTITY_H
#define ENTITY_H

#include <limits>
#include "abilities/abilities.h"
#include "managers/health_manager.h"

struct entity_definition
{
	enum class directions { right, left };
	explicit entity_definition(const std::type_index& type)
			: type(type) {}
	std::type_index type;
	std::string name;
	health_field health_pack;
	abilities entity_abilities;
	directions direction;
};

namespace entity_helper
{
inline entity_definition turned_right(entity_definition&& data)
{
	data.direction = entity_definition::directions::right;
	return data;
}
inline entity_definition turned_left(entity_definition&& data)
{
	data.direction = entity_definition::directions::left;
	return data;
}
};

#endif