//
// Created by abrdej on 15.11.17.
//

#ifndef PIGEONWAR_DROID_H
#define PIGEONWAR_DROID_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/laser.h"
#include <server/abilities/moveable.h>
#include <server/abilities/teleport.h>
#include <gui/entity_drawer.h>
#include <components/damage_taker.h>

class droid final
{
public:
	static auto create(std::uint32_t id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Droid";

		entity.add<health_field>(55);
		entity.add<damage_taker>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<laser>());
		abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<teleport>());

		entity.add<bitmap_field>(id, bitmap_key::droid);

		return entity;
	}
};

#endif //PIGEONWAR_DROID_H
