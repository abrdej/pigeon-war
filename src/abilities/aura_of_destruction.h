#pragma once

#include <abilities/abilities.h>
#include <abilities/per_turn_usable.h>

class aura_of_destruction : public passive_ability, per_turn_callback {
public:
    explicit aura_of_destruction(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(aura_of_destruction)
    DEFINE_DESC_ZERO(aura_of_destruction)

private:
    const std::uint32_t entity_id;
};
