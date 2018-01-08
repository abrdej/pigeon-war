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
    void play_animation(size_t from_index, size_t to_index);

private:
    const int damage{6};
    const int death_mark_duration{2};
    bool used{false};
};

#endif //PIGEONWAR_SHIRUKEN_H
