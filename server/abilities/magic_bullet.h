//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_MAGIC_BULLET_H
#define PIGEONWAR_MAGIC_BULLET_H

#include "ability.h"
#include "core/turn.h"

class magic_bullet final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    explicit magic_bullet(std::size_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::magic_bullet;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

private:
    const int range{4};
    int magic_power{0};
    int magic_power_accumulation_amount{10};
    int magic_power_drain_amount{5};
    bool used{false};
};

#endif //PIGEONWAR_MAGIC_BULLET_H
