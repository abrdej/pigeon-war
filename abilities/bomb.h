//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_BOMB_H
#define PIGEONWAR_BOMB_H

#include <entities/entity.h>
#include "abilities/ability.h"
#include "core/turn.h"
#include "moveable.h"
#include <boost/circular_buffer.hpp>
#include <managers/entity_manager.h>

class bomb_detonation final : public ability {
public:
	bomb_detonation(std::size_t bomb_id) : bomb_id(bomb_id) {}
	void prepare(size_t for_index) override;
	void use(size_t for_index);
private:
	std::size_t bomb_id;
	int damage{6};
};

struct bomb_instance {
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(bomb_instance));
		entity_def.name = "Bomba";
		entity_def.health_pack.base_health = indestructible;
		entity_def.health_pack.is_destructible = false;
		entity_def.entity_abilities.add_ability(abilities::ability_types::moving, std::make_shared<bomb_detonation>(id));
		return entity_def;
	}
};

class bomb final : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
	bomb();
	void prepare(size_t for_index) override;
	void use(size_t index_on);

private:
	bool used{false};
	int range{2};
	boost::circular_buffer<std::shared_ptr<std::size_t>> bombs;
};


#endif //PIGEONWAR_BOMB_H
