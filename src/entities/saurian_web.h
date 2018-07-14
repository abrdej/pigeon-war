#ifndef SAURIONS_WEB_H
#define SAURIONS_WEB_H

#include "entity.h"

struct saurian_web final
{
	static auto create(base_entity& entity)
	{
		entity.name = "Saurian Web";

		entity.add<health_field>(20);
		entity.add<damage_taker>();

		return entity;
	}
};

#endif