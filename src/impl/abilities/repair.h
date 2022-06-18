//
// Created by abrdej on 02.04.18.
//

#ifndef PIGEONWAR_REPAIR_H
#define PIGEONWAR_REPAIR_H

#include <caster_target_ability.h>
#include <turn_based/turn_system.h>

class repair  final : public caster_target_ability
{
public:
    explicit repair(std::uint32_t id);

    bitmap_key get_bitmap_key() const override {
        return "repair";
    }

    DEFINE_DESC_ONE(repair, repair_amount)

private:
    void use(std::uint32_t on_index) override;

    bool used_{false};
    std::uint32_t entity_id;
    std::int32_t repair_amount{25};
};


#endif //PIGEONWAR_REPAIR_H
