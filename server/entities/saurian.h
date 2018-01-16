#ifndef SURIAN_H
#define SURIAN_H

#include "entity.h"
#include "server/abilities/tongue_of_fire.h"

class saurian final
{
public:
	static auto create(std::uint64_t id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Saurion";

		entity.add<health_field>(35);
		entity.add<damage_taker>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<tongue_of_fire>());

		entity.add<bitmap_field>(id, bitmap_key::saurian);

		return entity;
	}
};

#endif