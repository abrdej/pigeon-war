//
// Created by abrdej on 09.01.18.
//

#ifndef PIGEONWAR_MODIFICATIONS_MANAGER_H
#define PIGEONWAR_MODIFICATIONS_MANAGER_H

#include <common/managers.h>

struct modification {
	int damage_receiver_modifier{0};
	int damage_dealer_modifier{0};
};

struct modifications_manager : base_manager<modification, modification&> {
	static void modify_damage_receiver_modifier_by(std::size_t entity_id, int x) {
		map_[entity_id].damage_receiver_modifier += x;
	}
	static void modify_damage_dealer_modifier_by(std::size_t entity_id, int x) {
		map_[entity_id].damage_dealer_modifier += x;
	}
	static int damage_receiver_modifier_value(std::size_t entity_id) {
		return map_[entity_id].damage_receiver_modifier;
	}
	static int damage_dealer_modifier_value(std::size_t entity_id) {
		return map_[entity_id].damage_dealer_modifier;
	}
};


#endif //PIGEONWAR_MODIFICATIONS_MANAGER_H
