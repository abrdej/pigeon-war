//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_FIRE_H
#define PIGEONWAR_FIRE_H

#include "entity.h"

struct fire final
{
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(fire));
		entity_def.name = "Ognisko";
		entity_def.health_pack.base_health = indestructible;
		entity_def.health_pack.is_destructible = false;
		return entity_def;
	}
};

#endif //PIGEONWAR_FIRE_H
