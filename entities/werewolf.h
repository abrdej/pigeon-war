#ifndef WEREWOLF_H
#define WEREWOLF_H

#include <abilities/drain.h>
#include <abilities/wolf_herd.h>
#include "entity.h"
#include "abilities/moveable.h"

struct werewolf final
{
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(werewolf));
		entity_def.name = "Wilkołak";
		entity_def.health_pack.base_health = 60;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<drain>());
		entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<wolf_herd>());
		return entity_def;
	}
};

#endif