//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_MOVING_H
#define PIGEONWAR_WRETCH_MOVING_H

#include "ability.h"
#include "core/turn.h"
#include <functional>

class wretch_moving final : public ability, turn_events_helper::every_turn_callback_helper {
public:
    explicit wretch_moving(sf::Uint64 entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::moveable;
    }

private:
    void prepare(sf::Uint64 for_index) override;
    void move(sf::Uint64 index_to);

private:
    std::uint64_t entity_id;
    std::int32_t max_range{4};
    std::int32_t range{4};
    const std::int32_t power_decrease_for_cost{2};
    bool used{false};
};


#endif //PIGEONWAR_WRETCH_MOVING_H
