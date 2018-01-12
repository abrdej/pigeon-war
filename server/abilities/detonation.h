//
// Created by abrde on 06.12.2017.
//

#ifndef PIGEONWAR_DETONATION_H
#define PIGEONWAR_DETONATION_H

#include "ability.h"
#include "core/turn.h"

class detonation : public ability {
public:
    explicit detonation(sf::Uint64 entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::detonation;
    }

private:
    void prepare(sf::Uint64 for_index) override {}
    sf::Uint64 entity_id;
    sf::Int32 damage{9};
    turn::turn_system::strong_receiver receiver;
};


#endif //PIGEONWAR_DETONATION_H
