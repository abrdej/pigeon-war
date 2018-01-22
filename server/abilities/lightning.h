//
// Created by abrde on 20.01.2018.
//

#ifndef PIGEONWAR_LIGHTNING_H
#define PIGEONWAR_LIGHTNING_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class lightning : public path_target_ability<3>, per_turn_usable {
public:
    explicit lightning(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::lightning;
    }

    std::string hint() const override;

private:
    void use(std::uint32_t index_on) override;

    std::uint32_t entity_id;
    std::int32_t damage{12};
    std::int32_t power_cost{8};
};

#endif //PIGEONWAR_LIGHTNING_H
