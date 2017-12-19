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
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(droid));
		entity_def.name = "Droid";
		entity_def.health_pack.base_health = 55;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		entity_def.entity_abilities.add_ability(abilities::ability_types::offensive, std::make_shared<laser>());
		entity_def.entity_abilities.add_ability(abilities::ability_types::special, std::make_shared<teleport>());

		entity_def.drawer = std::make_shared<entity_drawer>(id, bitmap_key::droid);

		return entity_def;
	}
};

#endif //PIGEONWAR_DROID_H
