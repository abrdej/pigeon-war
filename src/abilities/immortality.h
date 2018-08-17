#pragma once

#include <abilities/ability.h>
#include <core/turn_system.h>

class immortality : public passive_ability {
public:
    explicit immortality(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return "immortality";
    }

    DEFINE_DESC_ZERO(immortality)

private:
    const std::uint32_t entity_id;
    const std::int32_t duration{1};
    turn_scoped_connection immortality_holder;
};
