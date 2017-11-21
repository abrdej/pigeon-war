//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_BLOW_THE_AX_H
#define PIGEONWAR_BLOW_THE_AX_H


#include "ability.h"
#include "core/turn.h"

class blow_the_ax final : public ability, turn_events_helper::every_turn_callback_helper {
public:
    blow_the_ax();

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);

    int damage{20};
    bool used{false};
};


#endif //PIGEONWAR_BLOW_THE_AX_H
