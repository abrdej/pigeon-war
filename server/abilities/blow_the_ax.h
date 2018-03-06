//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_BLOW_THE_AX_H
#define PIGEONWAR_BLOW_THE_AX_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class blow_the_ax final : public straight_target_ability<1>,
                          per_turn_usable {
public:
    bitmap_key get_bitmap_key() const override {
        return bitmap_key::blow_the_ax;
    }

    DEFINE_DESC_ONE(blow_the_ax, damage)

private:
    void use(std::uint32_t index_on) override;

    std::int32_t damage{15};
};


#endif //PIGEONWAR_BLOW_THE_AX_H
