//
// Created by abrdej on 29.11.17.
//

#ifndef PIGEONWAR_THROWER_H
#define PIGEONWAR_THROWER_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include <abilities/rocket_launcher.h>
#include <abilities/change_rocket_type.h>

class thrower final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Rocket Thrower";

		entity.add<health_field>(40);
		entity.add<damage_taker>();
		entity.add<addition>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<rocket_launcher>());
		abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<change_rocket_type>(entity.entity_id));

		entity.add<bitmap_field>(entity.entity_id, bitmap_key::thrower);

		return entity;
	}
};

#endif //PIGEONWAR_THROWER_H
