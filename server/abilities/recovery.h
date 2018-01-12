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
    explicit recovery(sf::Uint64 id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::recovery;
    }

private:
    sf::Uint64 entity_id;
    sf::Int32 no_damage_counter{0};
    sf::Int32 no_move_counter{0};
    sf::Uint64 last_index{std::numeric_limits<sf::Uint64>::max()};
    const sf::Int32 recovery_amount_per_turn{10};
    const sf::Int32 required_no_damage{2};
    const sf::Int32 required_no_move{1};
};


#endif //PIGEONWAR_RECOVERY_H
