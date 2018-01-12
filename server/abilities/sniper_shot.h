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
    void prepare(sf::Uint64 for_index) override;
    void use(sf::Uint64 index_on);
    void play_animation(sf::Uint64 entity_id, sf::Uint64 from_index, sf::Uint64 to_index);

private:
    const sf::Int32 range{10};
    const sf::Int32 damage{12};
    const sf::Int32 additional_damage{12};
};

#endif //PIGEONWAR_SNIPER_SHOT_H
