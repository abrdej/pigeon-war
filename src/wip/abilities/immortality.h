#pragma once

#include <turn_based/ability.h>
#include <turn_based/turn_system.h>

class immortality : public passive_ability {
public:
    explicit immortality(std::uint32_t entity_id);

    bitmap_key get_name() const override {
        return "immortality";
    }

    DEFINE_DESC_ZERO(immortality)

private:
    const std::uint32_t entity_id;
    const std::int32_t duration{1};
    turn_scoped_connection immortality_holder;
};
