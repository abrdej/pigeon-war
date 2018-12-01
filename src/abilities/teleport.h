#pragma once

#include <abilities/ability.h>

class teleport final : public active_ability {
public:
    teleport() = default;

    ADD_BITMAP_GETTER(teleport)

    DEFINE_DESC_ZERO(teleport)

private:
    void prepare(std::uint32_t for_index) override;

    void use(std::uint32_t from_index, std::uint32_t to_index);

private:
    bool used{false};
};
