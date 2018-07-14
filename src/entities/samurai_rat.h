//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_SAMURAI_RAT_H
#define PIGEONWAR_SAMURAI_RAT_H

#include <abilities/abilities.h>
#include <abilities/dodge.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include "entity.h"
#include "abilities/moveable.h"
#include "abilities/sword_blow.h"


struct samurai_rat final
{
	static auto create(base_entity& entity)
	{
		entity.name = "Samurai";

		entity.add<health_field>(45);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(4));
		abilities_ptr->add_ability(std::make_shared<sword_blow>());
		abilities_ptr->add_ability(std::make_shared<dodge>(entity.entity_id));

		return entity;
	}
};

#endif //PIGEONWAR_SAMURAI_RAT_H
