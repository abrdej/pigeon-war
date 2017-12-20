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
    explicit power_circle(std::size_t entity_id);
    ~power_circle() override;

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::power_circle;
    }

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t index_on);

private:
    int damage{6};

    bool bonus_active{false};
    int bonus_counter{0};
    const int max_bonus_counter{3};

    int damage_reduction{0};

    int absorption_power{0};
    int max_absorption_power{15};

    using damage_receiver_type = std::function<int(health_field&, const damage_pack&)>;
    std::unordered_map<std::size_t, damage_receiver_type> dmg_rec_backup;
};

#endif //PIGEONWAR_POWER_CIRCLE_H
