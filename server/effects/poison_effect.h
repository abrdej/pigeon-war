//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_POISON_EFFECT_H
#define PIGEONWAR_POISON_EFFECT_H


#include <cstdint>
#include "base_effect.h"

class poison_effect : public base_effect {
	int32_t poison_damage;
	int32_t poison_duration;

	poison_effect(int32_t poison_damage, int32_t poison_duration) {

	}


};

#endif //PIGEONWAR_POISON_EFFECT_H
