//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_SNIPER_SHOT_H
#define PIGEONWAR_SNIPER_SHOT_H

#include "abilities/ability.h"
#include "core/turn.h"

class sniper_shot final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    sniper_shot();
    bitmap_key get_bitmap_key() const override {
        return bitmap_key::sniper_shot;
    }
private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(std::size_t entity_id, size_t from_index, size_t to_index);

private:
    const int range{10};
    const int damage{12};
    const int additional_damage{12};
    bool used{false};
};

#endif //PIGEONWAR_SNIPER_SHOT_H
