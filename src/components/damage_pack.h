//
// Created by abrdej on 16.01.18.
//

#ifndef PIGEONWAR_DAMAGE_PACK_H
#define PIGEONWAR_DAMAGE_PACK_H

#include <cstdint>
#include <limits>

static const std::uint32_t no_damage_dealer = std::numeric_limits<std::uint32_t>::max();

enum class damage_types {
	MELEE,
	RANGED,
	MAGIC,
	SPECIAL,
	HEALING,
	UNDEFINED
};

struct damage_pack {
	damage_pack(std::int32_t value, damage_types type, std::uint32_t receiver_id)
			: damage_value(value),
			  damage_receiver_id(receiver_id),
			  damage_type(type),
			  damage_dealer_id(no_damage_dealer) {}
	damage_pack(std::int32_t value, damage_types type, std::uint32_t receiver_id, std::uint32_t dealer_id)
			: damage_value(value),
			  damage_type(type),
			  damage_receiver_id(receiver_id),
			  damage_dealer_id(dealer_id) {}

	std::int32_t damage_value;
	damage_types damage_type;
	std::uint32_t damage_receiver_id;
	std::uint32_t damage_dealer_id;
};

enum class heal_types {
    above_base_health,
    to_base_health
};

struct heal_pack {
	heal_pack(std::int32_t value, std::uint32_t receiver_id, heal_types heal_type)
            : heal_value(value), receiver_id(receiver_id), heal_type(heal_type) {}
    std::int32_t heal_value;
    std::uint32_t receiver_id;
    heal_types heal_type;
};


inline damage_pack melee_damage(std::int32_t value, std::uint32_t receiver_id, std::uint32_t dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::MELEE, receiver_id, dealer_id};
}

inline damage_pack ranged_damage(std::int32_t value, std::uint32_t receiver_id, std::uint32_t dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::RANGED, receiver_id, dealer_id};
}

inline damage_pack magic_damage(std::int32_t value, std::uint32_t receiver_id, std::uint32_t dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::MAGIC, receiver_id, dealer_id};
}

inline damage_pack special_damage(std::int32_t value, std::uint32_t receiver_id, std::uint32_t dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::SPECIAL, receiver_id, dealer_id};
}

inline heal_pack healing_to_base_health(std::int32_t value, std::uint32_t receiver_id) {
	return heal_pack{value, receiver_id, heal_types::to_base_health};
}

inline heal_pack healing_above_base_health(std::int32_t value, std::uint32_t receiver_id) {
    return heal_pack{value, receiver_id, heal_types::above_base_health};
}

#endif //PIGEONWAR_DAMAGE_PACK_H
