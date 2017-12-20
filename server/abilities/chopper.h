//
// Created by abrde on 01.12.2017.
//

#ifndef PIGEONWAR_CHOPPER_H
#define PIGEONWAR_CHOPPER_H

#include "ability.h"
#include "core/turn.h"
#include <boost/circular_buffer.hpp>

class spiral_of_fire;

class chopper final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    explicit chopper(std::size_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::chopper;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t index_from, size_t index_on);

private:
    const int range = 1;
    const int no_fired_damage = 5;
    const int fired_damage = 10;
    std::size_t entity_id;
    bool used{false};
    int damage{no_fired_damage};
    bool fired{false};
    int fired_aura_dmg{3};
    int fired_counter{0};

    boost::circular_buffer<std::size_t> last_attacked{2};

    void set_fired();
    void remove_fired();

    friend class spiral_of_fire;
};


#endif //PIGEONWAR_CHOPPER_H
