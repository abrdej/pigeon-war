//
// Created by abrde on 27.01.2018.
//

#ifndef PIGEONWAR_AURA_OF_DESTRUCTION_H
#define PIGEONWAR_AURA_OF_DESTRUCTION_H

#include "ability.h"
#include "per_turn_usable.h"
#include "caster_target_ability.h"

class aura_of_destruction : public caster_target_ability, per_turn_callback {
public:
    explicit aura_of_destruction(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::aura_of_destruction;
    }

    std::string hint() const override;

    void use(std::uint32_t use_on_index) override;

private:
    std::uint32_t entity_id;
    std::int32_t damage_increase{1};
    std::int32_t usable_damage_increase{2};
    std::int32_t cost{10};
    std::int32_t duration{1};
};


#endif //PIGEONWAR_AURA_OF_DESTRUCTION_H
