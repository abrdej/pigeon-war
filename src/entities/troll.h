//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_TROLL_H
#define PIGEONWAR_TROLL_H

#include <abilities/moveable.h>
#include <abilities/bludgeon.h>
#include <abilities/rage.h>
#include <abilities/regeneration.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include <abilities/abilities.h>
#include "entity.h"

struct troll final
{
	static auto create(base_entity& entity)
	{
		entity.name = "Troll";

		entity.add<health_field>(80);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(3));
		abilities_ptr->add_ability(std::make_shared<bludgeon>(entity.entity_id));
		abilities_ptr->add_ability(std::make_shared<rage>(entity.entity_id));
		abilities_ptr->add_ability(std::make_shared<regeneration>(entity.entity_id));
	}
};

#endif //PIGEONWAR_TROLL_H
