#ifndef SAURIONS_WEB_H
#define SAURIONS_WEB_H

#include "entities/entity.h"

class saurions_web final
{
public:
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Saurion Web";
		entity_health(components).base_health = 20;

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::saurions_web);

		return components;
	}
};

#endif