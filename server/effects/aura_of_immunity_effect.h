//
// Created by abrdej on 18.01.18.
//

#ifndef PIGEONWAR_AURA_OF_IMMUNITY_EFFECT_H
#define PIGEONWAR_AURA_OF_IMMUNITY_EFFECT_H

#include "base_effect.h"

class aura_of_immunity_effect : public effect {
public:
	explicit aura_of_immunity_effect(std::uint32_t entity_id, std::int32_t damage_reduction)
            : entity_id(entity_id),
              damage_reduction(damage_reduction) {}
	bool set_effect(std::uint32_t entity_id) override;
	void remove_effect(std::uint32_t entity_id) override;

private:
    std::uint32_t entity_id;
    std::int32_t damage_reduction;
};


#endif //PIGEONWAR_AURA_OF_IMMUNITY_EFFECT_H
