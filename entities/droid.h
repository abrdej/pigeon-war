//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_DROID_H
#define PIGEONWAR_DROID_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/laser.h"
#include <abilities/moveable.h>
#include <abilities/teleport.h>
#include <gui/entity_drawer.h>

class droid final
{
public:
	static auto create(size_t id)
	{
		base_components components;
		entity_name(components) = "Droid";
		entity_health(components).base_health = 55;
		entity_abilities(components).add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		entity_abilities(components).add_ability(abilities::ability_types::offensive, std::make_shared<laser>());
		entity_abilities(components).add_ability(abilities::ability_types::special, std::make_shared<teleport>());

		entity_drawer_ptr(components) = std::make_shared<entity_drawer>(id, bitmap_key::droid);

		return components;
	}
};

#endif //PIGEONWAR_DROID_H
