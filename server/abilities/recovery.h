//
// Created by abrdej on 19.11.17.
//

#ifndef PIGEONWAR_RECOVERY_H
#define PIGEONWAR_RECOVERY_H

#include "ability.h"
#include "core/turn_system.h"

class recovery final : public passive_ability,
                       protected turn_callback_helper
{
public:
    explicit recovery(std::uint32_t id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::recovery;
    }

private:
    std::uint32_t entity_id;
    std::int32_t no_damage_counter{0};
    std::int32_t no_move_counter{0};
    std::uint32_t last_index{std::numeric_limits<std::uint32_t>::max()};
    const std::int32_t recovery_amount_per_turn{10};
    const std::int32_t required_no_damage{2};
    const std::int32_t required_no_move{1};
};


#endif //PIGEONWAR_RECOVERY_H
