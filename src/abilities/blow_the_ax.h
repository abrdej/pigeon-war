#pragma once

#include <abilities/straight_target_ability.h>
#include <abilities/per_turn_usable.h>

class blow_the_ax final : public straight_target_ability<1>,
                          per_turn_usable {
public:
    explicit blow_the_ax(std::uint32_t entity_id);
    bitmap_key get_bitmap_key() const override {
        return "blow_the_ax";
    }

    DEFINE_DESC_ONE(blow_the_ax, damage)

private:
    void use(std::uint32_t on_index) override;

private:
    std::uint32_t entity_id;
    std::int32_t damage{15};
};
