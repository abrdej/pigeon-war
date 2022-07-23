#pragma once

#include <turn_based/neighboring_target_ability.h>
#include <turn_based/per_turn_usable.h>

class poke final : public neighboring_target_ability<>, per_turn_usable
{
public:
    bitmap_key get_name() const override {
        return "poke";
    }
    ability_types type() const override {
        return ability_types::offensive;
    }

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage = 3;
};
