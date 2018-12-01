#pragma once

#include <abilities/neighboring_target_ability.h>
#include <abilities/per_turn_usable.h>

class suck_the_soul final : public neighboring_target_ability<>,
                            per_turn_usable {
public:
    explicit suck_the_soul(std::uint32_t entity_id);

    ADD_BITMAP_GETTER(drain)

private:
    void use(std::uint32_t index_on) override;

private:
    const std::int32_t damage{10};
    const std::int32_t duration{3};
    const std::int32_t suck_amount{5};

    std::vector<std::pair<std::uint32_t, std::int32_t>> souls;
    std::unordered_map<std::uint32_t, std::size_t> souls_mapped;
};
