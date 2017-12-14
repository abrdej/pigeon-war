//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_VICIOUS_CIRCLE_H
#define PIGEONWAR_VICIOUS_CIRCLE_H

#include <managers/health_manager.h>
#include "abilities/ability.h"
#include "core/turn.h"

class vicious_circle final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    explicit vicious_circle(std::size_t entity_id);

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t index_on);

private:

};

#endif //PIGEONWAR_VICIOUS_CIRCLE_H
