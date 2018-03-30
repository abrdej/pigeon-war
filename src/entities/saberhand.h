#ifndef SABERHAND_H
#define SABERHAND_H

#include "entity.h"
#include "abilities/abilities.h"
#include "abilities/moveable.h"
#include "abilities/sabers.h"
#include "abilities/invisibility.h"
#include "components/damage_taker.h"
#include "components/applied_effects.h"

class saberhand final
{
public:
	static auto create(base_entity& entity)
	{
		entity.name = "Saberhand";

		entity.add<health_field>(60);
		entity.add<damage_taker>();
		entity.add<applied_effects>();
		entity.add<modification>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<moveable>(4));
		abilities_ptr->add_ability(std::make_shared<sabers>());
		abilities_ptr->add_ability(std::make_shared<invisibility>(entity.entity_id));

		//entity.add<bitmap_field>(entity.entity_id, "saberhand);

		return entity;
	}
};

#endif