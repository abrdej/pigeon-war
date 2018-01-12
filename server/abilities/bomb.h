//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_BOMB_H
#define PIGEONWAR_BOMB_H

#include <entities/entity.h>
#include "ability.h"
#include "core/turn.h"
#include "moveable.h"
#include <boost/circular_buffer.hpp>
#include <managers/entity_manager.h>

class bomb_detonation final : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
	explicit bomb_detonation(sf::Uint64 bomb_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::bomb_detonation;
	}

	void prepare(sf::Uint64 for_index) override;
	void look_for_bombs();
	void use(sf::Uint64 for_index);
	void set_bomb_buffer(boost::circular_buffer<std::shared_ptr<sf::Uint64>>* p) {
		buffer = p;
	}
private:
	sf::Uint64 bomb_id;
	sf::Int32 damage{5};
	sf::Int32 final_damage{5};
	bool waited{false};
	boost::circular_buffer<std::shared_ptr<sf::Uint64>>* buffer{nullptr};
};

struct bomb_instance {
	static auto create(sf::Uint64 id)
	{
		base_components components;
		entity_name(components) = "Bomba";
		entity_health(components).base_health = indestructible;
		entity_health(components).is_destructible = false;
		entity_abilities(components).add_ability(abilities::ability_types::passive, std::make_shared<bomb_detonation>(id));
		return components;
	}
};

class bomb final : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
	bomb();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::bomb;
	}

	void prepare(sf::Uint64 for_index) override;
	void use(sf::Uint64 index_on);

private:
	sf::Uint64 find_min_health_jump(sf::Uint64 from_index, std::unordered_set<sf::Uint64>& visited_indexes);

	bool used{false};
	sf::Int32 range{3};
	sf::Int32 damage{7};
};


#endif //PIGEONWAR_BOMB_H
