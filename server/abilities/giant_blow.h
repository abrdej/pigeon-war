//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GIANT_BLOW_H
#define PIGEONWAR_GIANT_BLOW_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class giant_blow final : public neighboring_target_ability<>, per_turn_usable
{
public:

    bitmap_key get_bitmap_key() const override {
        return (counter == 2) ? bitmap_key::giant_blow_special : bitmap_key::giant_blow;
    }

    std::string hint() const override;

private:
    void use(size_t index_on) override;

private:
    const int damage{8};
    int counter{0};
};

#endif //PIGEONWAR_GIANT_BLOW_H
