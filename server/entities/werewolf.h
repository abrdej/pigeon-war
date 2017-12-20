#ifndef WEREWOLF_H
#define WEREWOLF_H

#include <server/abilities/drain.h>
#include <server/abilities/wolf_herd.h>
#include <gui/entity_drawer.h>
#include "entity.h"
#include "server/abilities/moveable.h"

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

		entity_bitmap_field(components) = bitmap_field(id, bitmap_key::werewolf);

		return components;
	}
};

#endif