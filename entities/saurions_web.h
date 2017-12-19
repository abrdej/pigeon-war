#ifndef SAURIONS_WEB_H
#define SAURIONS_WEB_H

#include "entities/entity.h"

class saurions_web final
{
public:
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(saurions_web));
		entity_def.name = "Paj�czyna jaszczura";
		entity_def.health_pack.base_health = 20;

		entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::saurions_web);

		return entity_def;
	}
};

#endif