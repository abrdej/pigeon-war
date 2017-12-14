//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_MOVING_H
#define PIGEONWAR_WRETCH_MOVING_H

#include "abilities/ability.h"
#include "core/turn.h"
#include <functional>

class wretch_moving final : public ability, turn_events_helper::every_turn_callback_helper {
public:
    explicit wretch_moving(std::size_t entity_id);

private:
    void prepare(size_t for_index) override;
    void move(size_t index_to);

private:
    int max_range{5};
    int range{5};
    bool used{false};
};


#endif //PIGEONWAR_WRETCH_MOVING_H
