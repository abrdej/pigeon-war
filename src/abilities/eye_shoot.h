//
// Created by abrdej on 02.04.18.
//

#ifndef PIGEONWAR_EYE_SHOOT_H
#define PIGEONWAR_EYE_SHOOT_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class eye_shoot final : public straight_target_ability<3>,
                        per_turn_usable {
public:
    eye_shoot();

    bitmap_key get_bitmap_key() const override {
        return "eye_shoot";
    }

    DEFINE_DESC(eye_shoot, base_damage, side_damage)

private:
    void use(std::uint32_t to_index) override;

private:
    const std::int32_t base_damage{8};
    const std::int32_t side_damage{16};
};


#endif //PIGEONWAR_EYE_SHOOT_H
