//
// Created by abrdej on 29.11.17.
//

#ifndef PIGEONWAR_THROWER_H
#define PIGEONWAR_THROWER_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include <abilities/rocket_launcher.h>
#include <abilities/mortar_thrower.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>

class thrower final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Rocket Thrower";

		entity.add<health_field>(40);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();
		entity.add<rocket_types>(rocket_types::long_range_rocket);

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(3));
		abilities_ptr->add_ability(std::make_shared<rocket_launcher>());
		abilities_ptr->add_ability(std::make_shared<mortar_thrower>());

		return entity;
	}
};

#endif //PIGEONWAR_THROWER_H
