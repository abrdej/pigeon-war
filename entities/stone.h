#ifndef STONE_H
#define STONE_H

#include "entity.h"

struct stone final
{
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Stone";
		entity_health(components).base_health = indestructible;
		entity_health(components).is_destructible = false;

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::stone);

		return components;
	}
};

#endif