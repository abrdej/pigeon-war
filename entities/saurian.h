#ifndef SURIAN_H
#define SURIAN_H

#include "entity.h"
#include "abilities/tongue_of_fire.h"

class saurian final
{
public:
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Saurion";
		entity_health(components).base_health = 35;
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<tongue_of_fire>());

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::saurian);

		return components;
	}
};

#endif