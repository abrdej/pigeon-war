//
// Created by abrdej on 11.11.17.
//

#ifndef PIGEONWAR_SWORD_BLOW_H
#define PIGEONWAR_SWORD_BLOW_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class sword_blow final : public neighboring_target_ability<>, per_turn_usable {
public:
    bitmap_key get_bitmap_key() const override {
        return bitmap_key::sword_blow;
    }
private:
    void use(size_t index_on) override;
    void play_sword_blow_animation(size_t from_index);

private:
    const int damage = 10;
};


#endif //PIGEONWAR_SWORD_BLOW_H
