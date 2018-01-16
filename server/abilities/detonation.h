//
// Created by abrde on 06.12.2017.
//

#ifndef PIGEONWAR_DETONATION_H
#define PIGEONWAR_DETONATION_H

#include "ability.h"
#include "core/turn_system.h"

class detonation : public ability {
public:
    explicit detonation(std::uint64_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::detonation;
    }

private:
    void prepare(std::uint64_t for_index) override {}
    std::uint64_t entity_id;
    std::int32_t damage{9};
    turn::turn_system::strong_receiver receiver;
};


#endif //PIGEONWAR_DETONATION_H
