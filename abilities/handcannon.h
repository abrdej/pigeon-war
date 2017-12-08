//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_HANDCANNON_H
#define PIGEONWAR_HANDCANNON_H

#include "abilities/ability.h"
#include "core/turn.h"

class handcannon final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    handcannon();
private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

private:
    const int range = 3;
    const int damage = 8;
    const int bonus_damage = 5;
    bool used{false};
};

#endif //PIGEONWAR_HANDCANNON_H
