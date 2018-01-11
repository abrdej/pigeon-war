//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_SHIRUKEN_H
#define PIGEONWAR_SHIRUKEN_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class shiruken final : public path_target_ability<4>, per_turn_usable
{
public:

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::shiruken;
    }

private:
    void use(size_t index_on) override;

private:
    const int damage{6};
    const int additional_damage_for_death_mark{6};
//    const int death_mark_duration{2};
};

#endif //PIGEONWAR_SHIRUKEN_H
