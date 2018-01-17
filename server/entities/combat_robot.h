//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_COMBAT_TOBOT_H
#define PIGEONWAR_COMBAT_TOBOT_H

#include <abilities/barrier.h>
#include "entity.h"
#include "components/damage_taker.h"
#include "components/additions.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include "server/abilities/missile_of_doom.h"

class combat_robot final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Combat Robot";

		entity.add<health_field>(50);
		entity.add<damage_taker>();
		entity.add<addition>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<missile_of_doom>(entity.entity_id));
		abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<barrier>(entity.entity_id));

		entity.add<bitmap_field>(entity.entity_id, bitmap_key::combat_robot);

		return entity;
	}
};

#endif //PIGEONWAR_COMBAT_TOBOT_H
