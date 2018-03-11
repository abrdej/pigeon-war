//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_ABSORBSION_H
#define PIGEONWAR_ABSORBSION_H

#include "ability.h"
#include "per_turn_usable.h"
#include <unordered_map>
#include <components/damage_pack.h>

class absorption final : public active_ability, per_turn_usable {
public:
    explicit absorption(std::uint32_t entity_id);
    ~absorption() override;

    bitmap_key get_bitmap_key() const override {
        return "absorption";
    }

    bool is_full() const {
        return absorption_power == max_absorption_power;
    }
    void set_empty() {
        absorption_power = 0;
    }
    void increase_dmg_reduction() {
        ++damage_reduction;
    }
    void zero_dmg_reduction() {
        damage_reduction = 0;
    }

private:
    void prepare(std::uint32_t for_index) override;
    void use(std::uint32_t index_on);
    void play_animation(std::uint32_t from_index, std::uint32_t to_index);

    const std::uint32_t entity_id;
    const std::int32_t range = 3;

    std::int32_t damage_reduction{0};

    std::int32_t absorption_power{0};
    std::int32_t max_absorption_power{15};

    using damage_receiver_type = std::function<std::int32_t(health_field&, const damage_pack&)>;
    std::uint32_t protected_id{std::numeric_limits<std::uint32_t>::max()};
    damage_receiver_type protected_dmg_rec_backup;
};

#endif //PIGEONWAR_ABSORBSION_H
