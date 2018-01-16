//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_FIRE_H
#define PIGEONWAR_FIRE_H

#include "entity.h"

struct fire final
{
	static auto create(base_entity& entity)
	{
		entity.name = "Fire";

		entity.add<health_field>();

		entity.add<bitmap_field>(entity.entity_id, bitmap_key::fire);

		return entity;
	}
};

#endif //PIGEONWAR_FIRE_H
