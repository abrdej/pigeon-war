#ifndef STONE_H
#define STONE_H

#include "entity.h"

struct stone final
{
	static auto create(sf::Uint64 id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Stone";

		entity.add<health_field>();

		entity.add<bitmap_field>(id, bitmap_key::stone);

		return entity;
	}
};

#endif