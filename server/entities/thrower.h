//
// Created by abrdej on 29.11.17.
//

#ifndef PIGEONWAR_THROWER_H
#define PIGEONWAR_THROWER_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include <server/abilities/flame_thrower.h>

class thrower final
{
public:
	static auto create(std::uint32_t id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Rocket Thrower";

		entity.add<health_field>(40);
		entity.add<damage_taker>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<flame_thrower>());
		abilities_ptr->add_ability(abilities::ability_types::special, std::make_shared<long_range_missile>());

		entity.add<bitmap_field>(id, bitmap_key::thrower);

		return entity;
	}
};

#endif //PIGEONWAR_THROWER_H
