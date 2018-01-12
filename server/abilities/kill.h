//
// Created by abrde on 24.12.2017.
//

#ifndef PIGEONWAR_KILL_H
#define PIGEONWAR_KILL_H

#include "abilities/ability.h"
#include "core/turn.h"

class kill final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    kill();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::kill;
    }

private:
    void prepare(sf::Uint64 for_index) override;
    void set_landing(sf::Uint64 for_index);
    void use(sf::Uint64 index_on);

private:
    const int range{3};
    const int damage{8};
    const int damage_with_killer_instinct{20};
    sf::Uint64 target_index;
    bool used{false};
};

#endif //PIGEONWAR_KILL_H
