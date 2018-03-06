//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_IMMORTALITY_H
#define PIGEONWAR_IMMORTALITY_H

#include "ability.h"
#include "core/turn_system.h"

class immortality : public passive_ability {
public:
    explicit immortality(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::immortality;
    }

    DEFINE_DESC_ZERO(immortality)

private:
    std::uint32_t entity_id;
    std::int32_t duration{1};
    turn_scoped_connection immortality_holder;
};

#endif //PIGEONWAR_IMMORTALITY_H
