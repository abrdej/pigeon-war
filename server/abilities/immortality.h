//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_IMMORTALITY_H
#define PIGEONWAR_IMMORTALITY_H

#include "ability.h"
#include "core/turn.h"

class immortality : public ability {
public:
    explicit immortality(std::size_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::immortality;
    }

private:
    void prepare(size_t for_index) override {}
    std::size_t entity_id;
    turn::turn_system::strong_receiver receiver;
};

#endif //PIGEONWAR_IMMORTALITY_H
