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

class bomb_detonation final : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
	explicit bomb_detonation(std::size_t bomb_id);
	void prepare(size_t for_index) override;
	void look_for_bombs();
	void use(size_t for_index);
	void set_bomb_buffer(boost::circular_buffer<std::shared_ptr<std::size_t>>* p) {
		buffer = p;
	}
private:
	std::size_t bomb_id;
	int damage{5};
	int final_damage{5};
	bool waited{false};
	boost::circular_buffer<std::shared_ptr<std::size_t>>* buffer{nullptr};
};

struct bomb_instance {
	static entity_definition create(size_t id)
	{
		entity_definition entity_def(typeid(bomb_instance));
		entity_def.name = "Bomba";
		entity_def.health_pack.base_health = indestructible;
		entity_def.health_pack.is_destructible = false;
		entity_def.entity_abilities.add_ability(abilities::ability_types::passive, std::make_shared<bomb_detonation>(id));
		return entity_def;
	}
};

class bomb final : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
	bomb();
	void prepare(size_t for_index) override;
	void use(size_t index_on);

private:
	int bombs_to_throw{2};
	int range{2};
	boost::circular_buffer<std::pair<std::shared_ptr<std::size_t>, bool>> bombs;
};


#endif //PIGEONWAR_BOMB_H
