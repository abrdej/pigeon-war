#pragma once

#include <turn_based/ability.h>

class stone_skin : public passive_ability {
public:
    explicit stone_skin(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(stone_skin)

    DEFINE_DESC(stone_skin, damage_reduction, reduction_increase_amount)

private:
    int damage_reduction{0};
    int reduction_increase_amount{1};
};
