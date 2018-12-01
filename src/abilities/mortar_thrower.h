#pragma once

#include <abilities/path_target_ability.h>
#include <abilities/per_turn_usable.h>

class mortar_thrower final : public path_target_ability<4>, per_turn_usable {
public:
    explicit mortar_thrower(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(flame_thrower)

    DEFINE_DESC(mortar_thrower, base_damage, rocket_change_bonus, range)

    bool was_used() const {
        return used;
    }
    void set_used() {
        used = true;
    }

private:
    void use(std::uint32_t on_index) override;

private:
    const std::uint32_t entity_id;
    const std::int32_t base_damage = 7;
    const std::int32_t rocket_change_bonus = 3;
};
