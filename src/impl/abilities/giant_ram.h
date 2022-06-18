//
// Created by abrde on 06.01.2018.
//

#ifndef PIGEONWAR_GIANT_RAM_H
#define PIGEONWAR_GIANT_RAM_H

#include <straight_target_ability.h>
#include <vector>

class giant_ram final : public straight_target_ability<5, target_types::enemy, true> {
public:
    explicit giant_ram(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return "giant_ram";
    }

    DEFINE_DESC_ONE(giant_ram, damage)

private:
    void prepare(std::uint32_t for_index) override;
    void use(std::uint32_t index_on) override;

private:
    std::uint32_t entity_id;
    const std::int32_t damage = 15;
    bool used{false};
};

#endif //PIGEONWAR_GIANT_RAM_H
