#ifndef NATIVE_H
#define NATIVE_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/drain.h"

class native final
{
public:
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(native));
		entity_def.name = "Tubylec";
		entity_def.health_pack.base_health = 50;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(5));
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<drain>());
		return entity_def;
	}
};

#endif