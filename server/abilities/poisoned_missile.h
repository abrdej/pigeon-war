//
// Created by abrdej on 14.11.17.
//

#ifndef PIGEONWAR_POISONED_MISSILE_H
#define PIGEONWAR_POISONED_MISSILE_H

#include "ability.h"
#include "core/turn.h"

class poisoned_missile final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    poisoned_missile();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::poisoned_missile;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

private:
    const int range{4};
    const int damage{6};
    const int poison_power{3};
    const int poison_last{3};
    bool used{false};
};

#endif //PIGEONWAR_POISONED_MISSILE_H
