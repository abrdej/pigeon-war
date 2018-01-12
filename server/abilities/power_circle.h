//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_POWER_CIRCLE_H
#define PIGEONWAR_POWER_CIRCLE_H

#include <managers/health_manager.h>
#include "ability.h"
#include "core/turn.h"

class power_circle final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    explicit power_circle(sf::Uint64 entity_id);
    ~power_circle() override;

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::power_circle;
    }

private:
    void prepare(sf::Uint64 for_index) override;
    void use(sf::Uint64 index_on);
    void play_animation(sf::Uint64 index_on);

private:
    sf::Int32 damage{6};

    bool bonus_active{false};
    sf::Int32 bonus_counter{0};
    const sf::Int32 max_bonus_counter{3};

    sf::Int32 damage_reduction{0};

    sf::Int32 absorption_power{0};
    sf::Int32 max_absorption_power{15};

    using damage_receiver_type = std::function<sf::Int32(health_field&, const damage_pack&)>;
    std::unordered_map<sf::Uint64, damage_receiver_type> dmg_rec_backup;
};

#endif //PIGEONWAR_POWER_CIRCLE_H
