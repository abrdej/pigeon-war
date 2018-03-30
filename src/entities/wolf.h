#ifndef wolf_H
#define wolf_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/basic_melee_attack.h"
#include "components/damage_taker.h"
#include "components/applied_effects.h"

class wolf final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Wolf";

		entity.add<health_field>(30);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(3));
		abilities_ptr->add_ability(std::make_shared<basic_melee_attack>());

		return entity;
	}
};

#endif