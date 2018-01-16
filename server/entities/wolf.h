#ifndef wolf_H
#define wolf_H

#include "entity.h"
#include "server/abilities/abilities.h"
#include "server/abilities/moveable.h"
#include "server/abilities/basic_melee_attack.h"
#include "gui/entity_drawer.h"
#include "damage_taker.h"

class wolf final
{
public:
	static auto create(sf::Uint64 id) {

		base_entity entity;
		entity.entity_id = id;
		entity.name = "Wolf";

		entity.add<health_field>(30);
		entity.add<damage_taker>();

		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(abilities::ability_types::moving, std::make_shared<moveable>(3));
		abilities_ptr->add_ability(abilities::ability_types::offensive, std::make_shared<basic_melee_attack>());

		entity.add<bitmap_field>(id, bitmap_key::wolf);

		return entity;
	}
};

#endif