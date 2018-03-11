//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_SHILED_H
#define PIGEONWAR_SHILED_H

#include "ability.h"

class shield : public passive_ability {
public:
    explicit shield(std::uint32_t entity_id);
    bitmap_key get_bitmap_key() const override {
        return "shield";
    }

    std::string hint() const override;

private:
    float range_attack_reduction{0.5f};
};

#endif //PIGEONWAR_SHILED_H
