#pragma once

#include <abilities/caster_target_ability.h>
#include <abilities/per_turn_usable.h>

class change_rocket_type final : public caster_target_ability,
                                 per_turn_usable {
public:
    explicit change_rocket_type(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(change_rocket_type)

private:
    void use(std::uint32_t index_on) override;

private:
    std::uint32_t entity_id;
};
