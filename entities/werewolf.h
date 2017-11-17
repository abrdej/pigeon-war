#ifndef WEREWOLF_H
#define WEREWOLF_H

#include <abilities/drain.h>
#include "entity.h"
#include "abilities/moveable.h"

struct werewolf final
{
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(werewolf));
		entity_def.name = "Troll";
		entity_def.health_pack.base_health = 70;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<drain>());
		return entity_def;
	}
};

#endif