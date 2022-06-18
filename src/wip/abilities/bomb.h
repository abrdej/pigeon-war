//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_BOMB_H
#define PIGEONWAR_BOMB_H

#include <turn_based/entity.h>
#include <turn_based/path_target_ability.h>
#include <turn_based/abilities.h>
#include <turn_based/turn_system.h>
#include <turn_based/moveable.h>
#include <boost/circular_buffer.hpp>
#include <turn_based/managers/entity_manager.h>

class bomb_detonation final : public active_ability, protected turn_callback_helper {
public:
	explicit bomb_detonation(std::uint32_t bomb_id);

	bitmap_key get_bitmap_key() const override {
		return "bomb_detonation";
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

class bomb final : public path_target_ability,
				   protected turn_callback_helper {
public:
	explicit bomb(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return "bomb";
	}

	void use(std::uint32_t index_on) override;

private:
	std::uint32_t entity_id;
	std::int32_t bombs{0};

};


#endif //PIGEONWAR_BOMB_H
