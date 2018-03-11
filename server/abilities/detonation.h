//
// Created by abrde on 06.12.2017.
//

#ifndef PIGEONWAR_DETONATION_H
#define PIGEONWAR_DETONATION_H

#include "ability.h"

class detonation : public active_ability {
public:
    explicit detonation(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return "detonation";
    }

private:
    void prepare(std::uint32_t for_index) override {}
    std::uint32_t entity_id;
    std::int32_t damage{9};
};


#endif //PIGEONWAR_DETONATION_H
