#ifndef STONE_H
#define STONE_H

#include "entity.h"

struct stone final
{
	static auto create(base_entity& entity)
	{
		entity.name = "Stone";

		entity.add<health_field>();

		entity.add<bitmap_field>(entity.entity_id, bitmap_key::stone);

		return entity;
	}
};

#endif