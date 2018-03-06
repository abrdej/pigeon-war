//
// Created by abrdej on 16.02.18.
//

#ifndef PIGEONWAR_DRAGON_SKIN_H
#define PIGEONWAR_DRAGON_SKIN_H

#include "ability.h"

class dragon_skin : public passive_ability {
public:
    explicit dragon_skin(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::dragon_skin;
    }

    DEFINE_DESC_ONE(dragon_skin, magic_damage_reduction)

private:
    float magic_damage_reduction{0.25f};
};


#endif //PIGEONWAR_DRAGON_SKIN_H
