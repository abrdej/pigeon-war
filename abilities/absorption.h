//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_ABSORBSION_H
#define PIGEONWAR_ABSORBSION_H

#include "abilities/ability.h"
#include <core/turn.h>
#include <unordered_map>

class absorption final : public ability, turn_events_helper::every_turn_callback_helper {
public:
    explicit absorption(std::size_t entity_id);
    ~absorption() override;

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::absorption;
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
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);

    const std::size_t entity_id;
    const int range = 3;
    bool used{false};

    int damage_reduction{0};

    int absorption_power{0};
    int max_absorption_power{15};

    using damage_receiver_type = std::function<int(health_field&, const damage_pack&)>;
    std::size_t protected_id{std::numeric_limits<std::size_t>::max()};
    damage_receiver_type protected_dmg_rec_backup;
};

#endif //PIGEONWAR_ABSORBSION_H
