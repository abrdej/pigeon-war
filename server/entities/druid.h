//
// Created by abrdej on 19.01.18.
//

#ifndef PIGEONWAR_DRUID_H
#define PIGEONWAR_DRUID_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include <server/abilities/moveable.h>
#include <components/damage_taker.h>
#include <components/additions.h>
#include <abilities/portal.h>
#include <abilities/cure.h>

class druid final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Druid";

		entity.add<health_field>(45);
		entity.add<damage_taker>();
		entity.add<addition>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		abilities_ptr->add_ability(abilities::ability_types::defensive, std::make_shared<cure>(entity.entity_id));
		abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<portal>());

		entity.add<bitmap_field>(entity.entity_id, bitmap_key::druid);

		return entity;
	}
};

#endif //PIGEONWAR_DRUID_H
