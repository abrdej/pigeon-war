//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_SHIRUKEN_H
#define PIGEONWAR_SHIRUKEN_H

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class shiruken final : public path_target_ability, per_turn_usable
{
public:
  shiruken() : path_target_ability(4) {}
  bitmap_key get_name() const override {
    return "shiruken";
  }

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage{6};
    const std::int32_t additional_damage_for_death_mark{6};
//    const std::int32_t death_mark_duration{2};
};

#endif //PIGEONWAR_SHIRUKEN_H
