//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_CHOPPER_H
#define PIGEONWAR_CHOPPER_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"
#include <boost/circular_buffer.hpp>

class spiral_of_fire;

class chopper final : public neighboring_target_ability<>, per_turn_usable
{
public:
    explicit chopper(sf::Uint64 entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::chopper;
    }

private:
    void use(sf::Uint64 index_on) override;

private:
    const sf::Int32 range = 1;
    const sf::Int32 no_fired_damage = 5;
    const sf::Int32 fired_damage = 10;
    sf::Uint64 entity_id;
    sf::Int32 damage{no_fired_damage};
    bool fired{false};
    sf::Int32 fired_aura_dmg{3};
    sf::Int32 fired_counter{0};

    boost::circular_buffer<sf::Uint64> last_attacked{2};

    void set_fired();
    void remove_fired();

    friend class spiral_of_fire;
};


#endif //PIGEONWAR_CHOPPER_H
