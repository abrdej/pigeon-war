//
// Created by abrde on 24.12.2017.
//

#ifndef PIGEONWAR_KILL_H
#define PIGEONWAR_KILL_H

#include "abilities/ability.h"
#include "core/turn.h"

class kill final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    kill();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::kill;
    }

private:
    void prepare(size_t for_index) override;
    void set_landing(size_t for_index);
    void use(size_t index_on);

private:
    const int range{4};
    const int damage{8};
    const int damage_with_killer_instinct{20};
    std::size_t target_index;
    bool used{false};
};

#endif //PIGEONWAR_KILL_H