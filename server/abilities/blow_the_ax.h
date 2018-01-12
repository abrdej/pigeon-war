//
// Created by abrdej on 17.11.17.
//

#ifndef PIGEONWAR_BLOW_THE_AX_H
#define PIGEONWAR_BLOW_THE_AX_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class blow_the_ax final : public straight_target_ability<1>,
                          per_turn_usable {
public:
    bitmap_key get_bitmap_key() const override {
        return bitmap_key::blow_the_ax;
    }

    std::string hint() const override {
        std::string desc;
        desc = "Blow The Ax - offensive ability that deals damage of: " + std::to_string(damage) + "\n";
        return std::move(desc);
    }

private:
    void use(size_t index_on) override;

    int damage{15};
};


#endif //PIGEONWAR_BLOW_THE_AX_H
