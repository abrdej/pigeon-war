//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GIANT_RAM_H
#define PIGEONWAR_GIANT_RAM_H

#include "straight_target_ability.h"
#include <vector>

class giant_ram final : public straight_target_ability<5, states::target_types::moving, true> {
public:
    giant_ram();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::giant_ram;
    }

private:
    void use(size_t index_on) override;
    void play_animation(size_t from_index, size_t to_index);

private:
    const int damage = 15;
    bool used{false};
};

#endif //PIGEONWAR_GIANT_RAM_H
