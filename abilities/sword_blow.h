//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_SWORD_BLOW_H
#define PIGEONWAR_SWORD_BLOW_H

#include "abilities/ability.h"
#include "core/turn.h"

class sword_blow final : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
    sword_blow();
private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_sword_blow_animation(size_t from_index);

private:
    const int range = 1;
    const int damage = 10;
    bool used{false};
};


#endif //PIGEONWAR_SWORD_BLOW_H
