//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GIANT_RAM_H
#define PIGEONWAR_GIANT_RAM_H

#include "ability.h"
#include <vector>

class giant_ram final : public ability {
public:
    giant_ram();

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::giant_ram;
    }

private:
    void prepare(size_t for_index) override;

    void use(size_t index_on);

    void play_animation(size_t from_index, size_t to_index);

private:
    const int range = 5;
    const int damage = 15;
    bool used{false};
};

#endif //PIGEONWAR_GIANT_RAM_H
