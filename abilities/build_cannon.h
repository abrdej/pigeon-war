//
// Created by abrdej on 20.11.17.
//

#ifndef PIGEONWAR_BUILD_CANNON_H
#define PIGEONWAR_BUILD_CANNON_H

#include <core/turn.h>
#include "abilities/ability.h"

class build_cannon : public ability, turn_events_helper::every_turn_callback_helper {
public:
    build_cannon();
    void prepare(size_t for_index) override;
    void use(size_t index_on);

private:
    bool built{false};
};


#endif //PIGEONWAR_BUILD_CANNON_H
