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
#include <components/applied_effects.h>

class droid final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Droid";

		entity.add<health_field>(55);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(3));
		abilities_ptr->add_ability(std::make_shared<laser>());
		abilities_ptr->add_ability(std::make_shared<teleport>());

		//entity.add<bitmap_field>(entity.entity_id, bitmap_key::droid);

		return entity;
	}
};

#endif //PIGEONWAR_DROID_H
