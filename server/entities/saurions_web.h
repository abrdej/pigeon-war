#ifndef SAURIONS_WEB_H
#define SAURIONS_WEB_H

#include "entity.h"

class saurions_web final
{
public:
	static auto create(sf::Uint64 id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Saurion Web";

		entity.add<health_field>(20);
		entity.add<damage_taker>();

		entity.add<bitmap_field>(id, bitmap_key::saurions_web);

		return entity;
	}
};

#endif