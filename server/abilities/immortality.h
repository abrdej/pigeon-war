//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_IMMORTALITY_H
#define PIGEONWAR_IMMORTALITY_H

#include "ability.h"
#include "core/turn.h"

class immortality : public passive_ability {
public:
    explicit immortality(sf::Uint64 entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::immortality;
    }

    std::string hint() const override;

private:
    sf::Uint64 entity_id;
    turn::turn_system::strong_receiver receiver;
};

#endif //PIGEONWAR_IMMORTALITY_H
