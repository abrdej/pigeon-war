//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_RECOVERY_H
#define PIGEONWAR_RECOVERY_H

#include "ability.h"
#include "core/turn.h"

class recovery final : public passive_ability,
                       protected turn_events_helper::every_turn_callback_helper
{
public:
    explicit recovery(std::size_t id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::recovery;
    }

private:
    std::size_t entity_id;
    int no_damage_counter{0};
    int no_move_counter{0};
    std::size_t last_index{std::numeric_limits<std::size_t>::max()};
    const int recovery_amount_per_turn{10};
    const int required_no_damage{2};
    const int required_no_move{1};
};


#endif //PIGEONWAR_RECOVERY_H
