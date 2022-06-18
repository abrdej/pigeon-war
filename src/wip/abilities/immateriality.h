#pragma once

#include <turn_based/abilities.h>
#include <turn_based/turn_system.h>

class immateriality : public passive_ability, protected turn_callback_helper {
public:
    explicit immateriality(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return "immateriality";
    }

    DEFINE_DESC_ZERO(immateriality)

private:
    bool is_active{true};
};
