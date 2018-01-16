//
// Created by abrdej on 16.01.18.
//

#ifndef PIGEONWAR_DAMAGE_PACK_H
#define PIGEONWAR_DAMAGE_PACK_H

#include <cstdint>
#include <limits>

static const std::uint64_t no_damage_dealer = std::numeric_limits<std::uint64_t>::max();

enum class damage_types {
	MELEE,
	RANGED,
	MAGIC,
	SPECIAL,
	UNDEFINED
};

struct damage_pack {
	damage_pack(std::int32_t value, damage_types type, std::uint64_t receiver_id)
			: damage_value(value),
			  damage_receiver_id(receiver_id),
			  damage_type(type),
			  damage_dealer_id(no_damage_dealer) {}
	damage_pack(std::int32_t value, damage_types type, std::uint64_t receiver_id, std::uint64_t dealer_id)
			: damage_value(value),
			  damage_type(type),
			  damage_receiver_id(receiver_id),
			  damage_dealer_id(dealer_id) {}

	std::int32_t damage_value;
	damage_types damage_type;
	std::uint64_t damage_receiver_id;
	std::uint64_t damage_dealer_id;
};

#endif //PIGEONWAR_DAMAGE_PACK_H
