//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_SHIRUKEN_H
#define PIGEONWAR_SHIRUKEN_H

#include "abilities/ability.h"
#include "core/turn.h"

class shiruken final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    shiruken();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::shiruken;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

private:
    const int range{4};
    const int damage{6};
    const int death_mark_duration{2};
    bool used{false};
};

#endif //PIGEONWAR_SHIRUKEN_H
