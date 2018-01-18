//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_TROLL_H
#define PIGEONWAR_TROLL_H

#include <server/abilities/moveable.h>
#include <server/abilities/bludgeon.h>
#include <server/abilities/rage.h>
#include <abilities/regeneration.h>
#include "entity.h"

struct troll final
{
	static auto create(base_entity& entity)
	{
		entity.name = "Troll";

		entity.add<health_field>(80);
		entity.add<damage_taker>();
		entity.add<addition>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<bludgeon>(entity.entity_id));
		abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<rage>(entity.entity_id));
		abilities_ptr->add_ability(abilities::ability_types::defensive, std::make_shared<regeneration>(entity.entity_id));

		entity.add<bitmap_field>(entity.entity_id, bitmap_key::troll);

		return entity;
	}
};

#endif //PIGEONWAR_TROLL_H
