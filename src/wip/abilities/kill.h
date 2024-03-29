//
// Created by abrde on 24.12.2017.
//

#ifndef PIGEONWAR_KILL_H
#define PIGEONWAR_KILL_H

#include <turn_based/ability.h>
#include <turn_based/turn_system.h>

class kill final : public active_ability, protected turn_callback_helper
{
public:
    kill();

    bitmap_key get_name() const override {
        return "kill";
    }

private:
    void prepare(std::uint32_t for_index) override;
    void set_landing(std::uint32_t for_index);
    void use(std::uint32_t index_on);

private:
    const int range{3};
    const int damage{6};
    const int damage_with_killer_instinct{25};
    std::uint32_t target_index;
    bool used{false};
};

#endif //PIGEONWAR_KILL_H
