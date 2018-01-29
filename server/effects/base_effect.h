//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_BASE_EFFECT_H
#define PIGEONWAR_BASE_EFFECT_H

#include <cstdint>

struct effect {
	virtual bool set_effect(std::uint32_t entity_id) = 0;
	virtual void remove_effect(std::uint32_t entity_id) = 0;
};

//struct base_aura_effect : effect {
//	virtual void set_aura() = 0;
//	virtual void remove_aura(std::uint32_t entity_id) = 0;
//};

struct base_effect {
	virtual ~base_effect() = default;
};

#endif //PIGEONWAR_BASE_EFFECT_H
