//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_POWER_CIRCLE_H
#define PIGEONWAR_POWER_CIRCLE_H

#include <turn_based/ability.h>
#include <turn_based/turn_system.h>
#include <components/damage_pack.h>
#include <components/health_field.h>

class power_circle final : public active_ability, protected turn_callback_helper
{
public:
    explicit power_circle(std::uint32_t entity_id);
    ~power_circle() override;

    bitmap_key get_bitmap_key() const override {
        return "power_circle";
    }

private:
    void prepare(std::uint32_t for_index) override;
    void use(std::uint32_t index_on);
    void play_animation(std::uint32_t index_on);

private:
    std::int32_t damage{6};

    bool bonus_active{false};
    std::int32_t bonus_counter{0};
    const std::int32_t max_bonus_counter{3};

    std::int32_t damage_reduction{0};

    std::int32_t absorption_power{0};
    std::int32_t max_absorption_power{15};

    using damage_receiver_type = std::function<std::int32_t(health_field&, const damage_pack&)>;
    std::unordered_map<std::uint32_t, damage_receiver_type> dmg_rec_backup;
};

#endif //PIGEONWAR_POWER_CIRCLE_H
