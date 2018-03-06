//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_BOMB_H
#define PIGEONWAR_BOMB_H

#include <entities/entity.h>
#include "path_target_ability.h"
#include "abilities.h"
#include "core/turn_system.h"
#include "moveable.h"
#include <boost/circular_buffer.hpp>
#include <managers/entity_manager.h>

class bomb_detonation final : public active_ability, protected turn_callback_helper {
public:
	explicit bomb_detonation(std::uint32_t bomb_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::bomb_detonation;
	}

	void prepare(std::uint32_t for_index) override;
	void look_for_bombs();
	void use(std::uint32_t for_index);
	void set_bomb_buffer(boost::circular_buffer<std::shared_ptr<std::uint32_t>>* p) {
		buffer = p;
	}
private:
	std::uint32_t bomb_id;
	std::int32_t damage{5};
	std::int32_t final_damage{5};
	bool waited{false};
	boost::circular_buffer<std::shared_ptr<std::uint32_t>>* buffer{nullptr};
};

struct bomb_instance {
	static auto create(std::uint32_t entity_id)
	{
		base_entity entity;
		entity.entity_id = entity_id;
		entity.name = "Bomba";
		entity.add<health_field>();
		auto abilities_ptr = entity.add<abilities>();
		abilities_ptr->add_ability(std::make_shared<bomb_detonation>(entity_id));
		return entity;
	}
};

class bomb final : public path_target_ability<4, target_types::moving, true>,
				   protected turn_callback_helper {
public:
	bomb();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::bomb;
	}

	void prepare(std::uint32_t for_index) override;
	void use(std::uint32_t index_on);

private:
};


#endif //PIGEONWAR_BOMB_H
