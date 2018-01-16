//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_SWORD_BLOW_H
#define PIGEONWAR_SWORD_BLOW_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class sword_blow final : public neighboring_target_ability<>, per_turn_usable {
public:
    bitmap_key get_bitmap_key() const override {
        return bitmap_key::sword_blow;
    }

    std::string hint() const override;

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage = 10;
};


#endif //PIGEONWAR_SWORD_BLOW_H
