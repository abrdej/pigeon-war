//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_TROLL_H
#define PIGEONWAR_TROLL_H

#include <server/abilities/moveable.h>
#include <server/abilities/bludgeon.h>
#include <server/abilities/rage.h>
#include "entity.h"

struct troll final
{
	static auto create(std::uint32_t id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Troll";

		entity.add<health_field>(80);
		entity.add<damage_taker>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(2));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<bludgeon>());
		abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<rage>(id));

		entity.add<bitmap_field>(id, bitmap_key::troll);

		return entity;
	}
};

#endif //PIGEONWAR_TROLL_H
