#pragma once

#include <abilities/path_target_ability.h>

class transmission final : public path_target_ability<4, target_types::all> {
public:
    explicit transmission(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(transmission)

    DEFINE_DESC_ZERO(transmission)

private:
    void use(std::uint32_t on_index) override;

    void transmit(std::uint32_t to_index);

private:
    std::uint32_t entity_id;
    bool used{false};
    std::uint32_t from_index;
};
