//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_INTERCEPTION_H
#define PIGEONWAR_INTERCEPTION_H

#include "ability.h"
#include "core/turn.h"

class interception final : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
    explicit interception(sf::Uint64 entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::interception;
    }

private:
    void prepare(sf::Uint64 for_index) override;
    void use(sf::Uint64 index_on);
    void play_animation(sf::Uint64 index_from, sf::Uint64 index_on);

    const sf::Int32 range = 1;
    const sf::Int32 damage = 12;
    sf::Int32 damage_accumulated{0};
    bool is_active{false};
    bool used{false};
};


#endif //PIGEONWAR_INTERCEPTION_H
