//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_ABSORBSION_H
#define PIGEONWAR_ABSORBSION_H

#include "ability.h"
#include <core/turn.h>
#include <unordered_map>

class absorption final : public ability, turn_events_helper::every_turn_callback_helper {
public:
    explicit absorption(sf::Uint64 entity_id);
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
    void prepare(sf::Uint64 for_index) override;
    void use(sf::Uint64 index_on);
    void play_animation(sf::Uint64 from_index, sf::Uint64 to_index);

    const sf::Uint64 entity_id;
    const sf::Int32 range = 3;
    bool used{false};

    sf::Int32 damage_reduction{0};

    sf::Int32 absorption_power{0};
    sf::Int32 max_absorption_power{15};

    using damage_receiver_type = std::function<sf::Int32(health_field&, const damage_pack&)>;
    sf::Uint64 protected_id{std::numeric_limits<sf::Uint64>::max()};
    damage_receiver_type protected_dmg_rec_backup;
};

#endif //PIGEONWAR_ABSORBSION_H
