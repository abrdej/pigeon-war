#ifndef STONE_H
#define STONE_H

#include "entity.h"

struct stone final
{
	static entity_data create()
	{
		entity_data data(typeid(stone));
		data.name = "Kamie�";
		data.health = indestructible;
		return data;
	}
};

#endif