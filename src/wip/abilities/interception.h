//
// Created by abrde on 13.12.2017.
//

#ifndef PIGEONWAR_INTERCEPTION_H
#define PIGEONWAR_INTERCEPTION_H

#include <turn_based/ability.h>
#include <turn_based/turn_system.h>

class interception final : public active_ability, protected turn_callback_helper {
public:
    explicit interception(std::uint32_t entity_id);

    bitmap_key get_name() const override {
        return "interception";
    }

private:
    void prepare(std::uint32_t for_index) override;
    void use(std::uint32_t index_on);
    void play_animation(std::uint32_t index_from, std::uint32_t index_on);

    const std::int32_t range = 1;
    const std::int32_t damage = 12;
    std::int32_t damage_accumulated{0};
    bool is_active{false};
    bool used{false};
};


#endif //PIGEONWAR_INTERCEPTION_H
