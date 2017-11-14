#ifndef SAURIONS_WEB_H
#define SAURIONS_WEB_H

#include "entities/entity.h"

class saurions_web final
{
public:
	static entity_definition create()
	{
		entity_definition entity_def(typeid(saurions_web));
		entity_def.name = "Paj�czyna jaszczura";
		entity_def.health_pack.base_health = 20;
		return entity_def;
	}
};

#endif