//
// Created by abrdej on 17.01.18.
//

#ifndef PIGEONWAR_BARRIER_H
#define PIGEONWAR_BARRIER_H

#include "ability.h"
#include "core/turn_system.h"

class barrier : public passive_ability {
public:
    explicit barrier(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return "immortality";
    }

    std::string hint() const override;

private:
    std::uint32_t entity_id;
    std::int32_t duration{2};
    bool is_barrier_active{false};
    bool was_barrier_active{false};
    std::int32_t barrier_strength{20};
    turn_scoped_connection barrier_holder;
};


#endif //PIGEONWAR_BARRIER_H
