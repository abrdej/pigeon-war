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
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Rocket Thrower";
		entity_health(components).base_health = 40;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<flame_thrower>());
		entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<long_range_missile>());

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::thrower);

		return components;
	}
};

#endif //PIGEONWAR_THROWER_H
