#ifndef SAURIONS_WEB_H
#define SAURIONS_WEB_H

#include "entity.h"

class saurions_web final
{
public:
	static auto create(sf::Uint64 id)
	{
		base_components components;
		entity_name(components) = "Saurion Web";
		entity_health(components).base_health = 20;

		entity_bitmap_field(components) = bitmap_field(id, bitmap_key::saurions_web);

		return components;
	}
};

#endif