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
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(troll));
		entity_def.name = "Troll";
		entity_def.health_pack.base_health = 70;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(2));
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<bludgeon>());
		entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<rage>(id));
		return entity_def;
	}
};

#endif //PIGEONWAR_TROLL_H
