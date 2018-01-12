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
		base_components components;
		entity_name(components) = "Fire";
		entity_health(components).base_health = indestructible;
		entity_health(components).is_destructible = false;

		entity_bitmap_field(components) = bitmap_field(id, bitmap_key::fire);

		return components;
	}
};

#endif //PIGEONWAR_FIRE_H
