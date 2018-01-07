//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_VICIOUS_CIRCLE_H
#define PIGEONWAR_VICIOUS_CIRCLE_H

#include <managers/health_manager.h>
#include "ability.h"
#include "core/turn.h"
#include "possible_move_helper.h"

class vicious_circle final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    explicit vicious_circle(std::size_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::magic_energy;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t index_on);

    std::size_t entity_id;
    int range{3};
    bool used{false};
};

#endif //PIGEONWAR_VICIOUS_CIRCLE_H
