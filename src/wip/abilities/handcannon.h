//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_HANDCANNON_H
#define PIGEONWAR_HANDCANNON_H

#include <straight_target_ability.h>
#include <turn_based/per_turn_usable.h>

class handcannon final : public straight_target_ability<3>,
                         per_turn_usable
{
public:
    bitmap_key get_name() const override {
        return "handcannon";
    }

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage = 12;
    const std::int32_t bonus_damage = 0;
};

#endif //PIGEONWAR_HANDCANNON_H
