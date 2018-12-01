#pragma once

#include <abilities/ability.h>

class surroundings : public passive_ability {
public:
    explicit surroundings(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(surroundings)

    DEFINE_DESC(surroundings, damage_reduction, min_damage)

private:
    int damage_reduction{3};
    int min_damage{3};
};
