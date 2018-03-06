#ifndef SAURIONS_WEB_H
#define SAURIONS_WEB_H

#include "entity.h"

class saurions_web final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Saurion Web";

		entity.add<health_field>(20);
		entity.add<damage_taker>();

		return entity;
	}
};

#endif