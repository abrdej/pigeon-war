//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_MAGIC_BULLET_H
#define PIGEONWAR_MAGIC_BULLET_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class magic_bullet final : public path_target_ability<4>, protected per_turn_callback
{
public:
    explicit magic_bullet(std::size_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::magic_bullet;
    }

    std::string hint() const override;

private:
    void use(size_t index_on);

private:
    int magic_power{0};
    int magic_power_accumulation_amount{10};
    int magic_power_drain_amount{5};
    bool used{false};
};

#endif //PIGEONWAR_MAGIC_BULLET_H
