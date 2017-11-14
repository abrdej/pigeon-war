#ifndef STONE_H
#define STONE_H

#include "entity.h"

struct stone final
{
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(stone));
		entity_def.name = "Kamie�";
		entity_def.health_pack.base_health = indestructible;
		return entity_def;
	}
};

#endif