#pragma once

#include <abilities/ability.h>

class dodge final : public passive_ability {
public:
    explicit dodge(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(dodge)

    DEFINE_DESC_ONE(dodge, counter)

private:
    int counter{0};
};
