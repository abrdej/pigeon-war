#ifndef WEREWOLF_H
#define WEREWOLF_H

#include <abilities/drain.h>
#include <abilities/wolf_herd.h>
#include <gui/entity_drawer.h>
#include "entity.h"
#include "abilities/moveable.h"

struct werewolf final
{
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Werewolf";
		entity_health(components).base_health = 60;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<drain>());
		entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<wolf_herd>());

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::werewolf);

		return components;
	}
};

#endif