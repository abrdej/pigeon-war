//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GIANT_RAM_H
#define PIGEONWAR_GIANT_RAM_H

#include "straight_target_ability.h"
#include <vector>

class giant_ram final : public straight_target_ability<5, states::target_types::enemy, true> {
public:
    explicit giant_ram(sf::Uint64 entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::giant_ram;
    }

    std::string hint() const override;

private:
    void prepare(sf::Uint64 for_index) override;
    void use(sf::Uint64 index_on) override;

private:
    sf::Uint64 entity_id;
    const sf::Int32 damage = 15;
    bool used{false};
};

#endif //PIGEONWAR_GIANT_RAM_H
