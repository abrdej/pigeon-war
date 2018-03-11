//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_MAGIC_BULLET_H
#define PIGEONWAR_MAGIC_BULLET_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class magic_bullet final : public path_target_ability<3>, protected per_turn_callback
{
public:
    explicit magic_bullet(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return "magic_bullet";
    }

    std::string hint() const override;

private:
    void use(std::uint32_t index_on);

private:
    std::int32_t magic_power{10};
    std::int32_t magic_power_accumulation_amount{10};
    std::int32_t magic_power_drain_amount{4};
    bool used{false};
    bool first_used{false};
};

#endif //PIGEONWAR_MAGIC_BULLET_H
