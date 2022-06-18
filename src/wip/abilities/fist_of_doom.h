//
// Created by abrde on 28.01.2018.
//

#ifndef PIGEONWAR_FIST_OF_DOOM_H
#define PIGEONWAR_FIST_OF_DOOM_H

#include <turn_based/ability.h>

class fist_of_doom : public active_ability {
public:
    explicit fist_of_doom(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return "fist_of_doom";
    }

    std::string hint() const override;

    void prepare(std::uint32_t for_index) override;

private:
    void use(std::uint32_t index_on);

    std::uint32_t entity_id;
    std::int32_t damage_per_power{5};
    bool used{false};
};

#endif //PIGEONWAR_FIST_OF_DOOM_H
