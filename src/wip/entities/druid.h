//
// Created by abrdej on 19.01.18.
//

#ifndef PIGEONWAR_DRUID_H
#define PIGEONWAR_DRUID_H

#include <turn_based/entity.h>
#include <turn_based/abilities.h>
#include <turn_based/move.h>
#include <components/damage_taker.h>
#include <components/applied_effects.h>
#include <abilities/portal.h>
#include <abilities/cure.h>
#include <abilities/lightning.h>
#include <components/power_field.h>

class druid final
{
public:
	static void create(base_entity& entity)
	{
		entity.name = "Druid";

		entity.add<health_field>(45);
		entity.add<power_filed>(entity.entity_id, 10, 10, 25);
		// entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(4));
		abilities_ptr->add_ability(std::make_shared<lightning>(entity.entity_id));
		abilities_ptr->add_ability(std::make_shared<cure>(entity.entity_id));
		abilities_ptr->add_ability(std::make_shared<portal>(entity.entity_id));
	}
};

#endif //PIGEONWAR_DRUID_H
