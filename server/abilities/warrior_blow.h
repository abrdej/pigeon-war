//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_WARRIOR_BLOW_H
#define PIGEONWAR_WARRIOR_BLOW_H

#include "ability.h"
#include "core/turn.h"

class warrior_blow final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    warrior_blow();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::warrior_blow;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t index_from, size_t index_on);

private:
    const size_t range = 1;
    const size_t damage = 10;
    const size_t damage_per_factor = 2;
    bool used{false};
};


#endif //PIGEONWAR_WARRIOR_BLOW_H
