//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GIANT_BLOW_H
#define PIGEONWAR_GIANT_BLOW_H

#include "ability.h"
#include "core/turn.h"

class giant_blow final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    giant_blow();

    bitmap_key get_bitmap_key() const override {
        return (counter == 2) ? bitmap_key::giant_blow_special : bitmap_key::giant_blow;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t index_from, size_t index_on);

private:
    const int range = 1;
    const int damage = 8;
    bool used{false};
    int counter{0};
};

#endif //PIGEONWAR_GIANT_BLOW_H
