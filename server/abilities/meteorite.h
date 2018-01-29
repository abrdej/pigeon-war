//
// Created by abrdej on 29.01.18.
//

#ifndef PIGEONWAR_METEORITE_H
#define PIGEONWAR_METEORITE_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class meteorite : public ability, per_turn_usable {
public:
    explicit meteorite(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::meteorite;
    }

    std::string hint() const override;

    void prepare(std::uint32_t for_index) override;

private:
    void use(std::uint32_t index_on);

    std::uint32_t entity_id;
    std::int32_t damage{18};
    std::int32_t power_cost{12};

    callback_holder meteorite_holder;
};

#endif //PIGEONWAR_METEORITE_H
