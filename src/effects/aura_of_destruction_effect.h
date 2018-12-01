#pragma once

#include <effects/base_effect.h>

class aura_of_destruction_effect : public effect {
public:
    explicit aura_of_destruction_effect(std::uint32_t entity_id, std::int32_t damage_increase)
            : entity_id(entity_id), damage_increase(damage_increase) {}
    bool set_effect(std::uint32_t entity_id) override;
    void remove_effect(std::uint32_t entity_id) override;

private:
    std::uint32_t entity_id;
    std::int32_t damage_increase;
};
