//
// Created by abrde on 06.12.2017.
//

#ifndef PIGEONWAR_DETONATION_H
#define PIGEONWAR_DETONATION_H

#include "ability.h"
#include "core/turn.h"

class detonation : public ability {
public:
    explicit detonation(std::size_t entity_id);

private:
    void prepare(size_t for_index) override {}
    std::size_t entity_id;
    int damage{9};
    turn::turn_system::strong_receiver receiver;
};


#endif //PIGEONWAR_DETONATION_H
