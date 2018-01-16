//
// Created by abrde on 07.12.2017.
//

#ifndef PIGEONWAR_SNIPER_SHOT_H
#define PIGEONWAR_SNIPER_SHOT_H

#include "ability.h"
#include "per_turn_usable.h"

class sniper_shot final : public ability, per_turn_usable
{
public:
    bitmap_key get_bitmap_key() const override {
        return bitmap_key::sniper_shot;
    }

    std::string hint() const override;

private:
    void prepare(std::uint32_t for_index) override;
    void use(std::uint32_t index_on);
    void play_animation(std::uint32_t entity_id, std::uint32_t from_index, std::uint32_t to_index);

private:
    const std::int32_t range{10};
    const std::int32_t damage{12};
    const std::int32_t additional_damage{12};
};

#endif //PIGEONWAR_SNIPER_SHOT_H
