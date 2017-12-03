//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_SPEAR_H
#define PIGEONWAR_SPEAR_H

#include "abilities/ability.h"
#include "core/turn.h"

class spear final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    spear(std::size_t id);
private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

private:
    static const int range = 1;
    static const int damage = 6;
    bool used{false};
    int accumulated_damage{0};
    std::size_t entity_id;
};


#endif //PIGEONWAR_SPEAR_H
