#ifndef SURIAN_H
#define SURIAN_H

#include "entity.h"
#include "abilities/tongue_of_fire.h"

class saurian final
{
public:
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(saurian));
		entity_def.name = "Jaszczur";
		entity_def.health_pack.base_health = 35;
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<tongue_of_fire>());

		entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::saurian);

		return entity_def;
	}
};

#endif