//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_INTERCEPTION_H
#define PIGEONWAR_INTERCEPTION_H

#include "ability.h"
#include "core/turn.h"

class interception final : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
    explicit interception(std::size_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::interception;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t index_from, size_t index_on);

    const int range = 1;
    const int damage = 12;
    int damage_accumulated{0};
    bool is_active{false};
    bool used{false};
};


#endif //PIGEONWAR_INTERCEPTION_H
