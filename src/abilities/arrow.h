//
// Created by abrde on 27.01.2018.
//

#ifndef PIGEONWAR_ARROW_H
#define PIGEONWAR_ARROW_H

#include "path_target_ability.h"
#include "per_turn_usable.h"

class arrow final : public path_target_ability<3>, per_turn_usable
{
public:
    bitmap_key get_bitmap_key() const override {
        return "arrow";
    }

    ABILITY_TYPE(offensive)
    DEFINE_DESC(arrow, damage, viewfinder_duration, range)

    void prepare(std::uint32_t for_index) override;

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage{10};
    const std::int32_t viewfinder_duration{3};

    std::unordered_set<std::uint32_t> entities_with_viewfinder;
};

#endif //PIGEONWAR_ARROW_H
