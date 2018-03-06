#ifndef SURIAN_H
#define SURIAN_H

#include "entity.h"
#include "server/abilities/tongue_of_fire.h"
#include "server/components/applied_effects.h"

class saurian final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Saurion";

		entity.add<health_field>(35);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<tongue_of_fire>());

		return entity;
	}
};

#endif