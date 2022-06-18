//
// Created by abrdej on 29.01.18.
//

#ifndef PIGEONWAR_WIZZARD_H
#define PIGEONWAR_WIZZARD_H

#include <turn_based/entity.h>
#include <turn_based/abilities.h>
#include <turn_based/moveable.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include <components/power_field.h>
#include <abilities/meteorite.h>
#include <abilities/purification.h>

class wizzard final
{
public:
	static void create(base_entity& entity)
	{
		entity.name = "Wizzard";

		entity.add<health_field>(45);
		entity.add<power_filed>(entity.entity_id, 10, 10, 30);
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(4));
		abilities_ptr->add_ability(std::make_shared<meteorite>(entity.entity_id));
		abilities_ptr->add_ability(std::make_shared<purification>(entity.entity_id));
	}
};

#endif //PIGEONWAR_WIZZARD_H
