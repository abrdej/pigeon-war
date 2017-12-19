//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_TROLL_H
#define PIGEONWAR_TROLL_H

#include <abilities/moveable.h>
#include <abilities/bludgeon.h>
#include <abilities/rage.h>
#include "entity.h"

struct troll final
{
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Troll";
		entity_health(components).base_health = 70;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(2));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<bludgeon>());
		entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<rage>(id));

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::troll);

		return components;
	}
};

#endif //PIGEONWAR_TROLL_H
