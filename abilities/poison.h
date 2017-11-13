//
// Created by abrdej on 12.11.17.
//

#ifndef PIGEONWAR_POISON_H
#define PIGEONWAR_POISON_H

#include "abilities/ability.h"
#include <vector>
#include "core/turn.h"

struct poison final : public ability, protected turn_events_helper::every_turn_callback_helper
{
    poison();
    void prepare(size_t for_index) override;
};


#endif //PIGEONWAR_POISON_H
