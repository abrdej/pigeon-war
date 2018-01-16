//
// Created by abrdej on 09.01.18.
//

#ifndef PIGEONWAR_MODIFICATIONS_MANAGER_H
#define PIGEONWAR_MODIFICATIONS_MANAGER_H

#include <common/managers.h>

class modification {
	std::int32_t damage_receiver_modifier{0};
    std::int32_t damage_dealer_modifier{0};

public:
    void modify_damage_receiver_modifier_by(std::int32_t x) {
        damage_receiver_modifier += x;
    }
    void modify_damage_dealer_modifier_by(std::int32_t x) {
        damage_dealer_modifier += x;
    }
    std::int32_t damage_receiver_modifier_value() const {
        return damage_receiver_modifier;
    }
    std::int32_t damage_dealer_modifier_value() const {
        return damage_dealer_modifier;
    }
};

#endif //PIGEONWAR_MODIFICATIONS_MANAGER_H
