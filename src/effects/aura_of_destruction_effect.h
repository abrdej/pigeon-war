//
// Created by abrde on 27.01.2018.
//

#ifndef PIGEONWAR_AURA_OF_DESTRUCTION_EFFECT_H
#define PIGEONWAR_AURA_OF_DESTRUCTION_EFFECT_H


#include "base_effect.h"

class aura_of_destruction_effect : public effect {
public:
    explicit aura_of_destruction_effect(std::uint32_t entity_id, std::int32_t damage_increase)
            : entity_id(entity_id), damage_increase(damage_increase) {}
    bool set_effect(std::uint32_t entity_id) override;
    void remove_effect(std::uint32_t entity_id) override;

private:
    std::uint32_t entity_id;
    std::int32_t damage_increase;
};


#endif //PIGEONWAR_AURA_OF_DESTRUCTION_EFFECT_H
