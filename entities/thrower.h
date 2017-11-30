//
// Created by abrdej on 29.11.17.
//

#ifndef PIGEONWAR_THROWER_H
#define PIGEONWAR_THROWER_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include <abilities/flame_thrower.h>

class thrower final
{
public:
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(thrower));
		entity_def.name = "Miotacz";
		entity_def.health_pack.base_health = 40;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<flame_thrower>());
		return entity_def;
	}
};

#endif //PIGEONWAR_THROWER_H
