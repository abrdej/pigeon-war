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

		return entity;
	}
};

#endif //PIGEONWAR_DROID_H
