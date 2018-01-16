#ifndef NATIVE_H
#define NATIVE_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/drain.h"
#include "server/abilities/counterattack.h"

class native final
{
public:
	static auto create(sf::Uint64 id)
	{
		base_entity entity;
		entity.entity_id = id;
		entity.name = "Native";

		entity.add<health_field>(50);
		entity.add<damage_taker>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(4));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<drain>());
		abilities_ptr->add_ability(abilities::ability_types::passive, std::make_shared<counterattack>(id));

		entity.add<bitmap_field>(id, bitmap_key::native);

		return entity;
	}
};

#endif