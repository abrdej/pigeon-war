//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_FIRE_H
#define PIGEONWAR_FIRE_H

#include "entity.h"

struct fire final
{
	static auto create(sf::Uint64 id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Fire";

		entity.add<health_field>();

		entity.add<bitmap_field>(id, bitmap_key::fire);

		return entity;
	}
};

#endif //PIGEONWAR_FIRE_H
