//
// Created by abrdej on 31.03.18.
//

#ifndef PIGEONWAR_CHARGE_H
#define PIGEONWAR_CHARGE_H

#include "neighboring_target_ability.h"
#include "per_turn_usable.h"

class charge final : public neighboring_target_ability<>,
                     turn_callback_helper {
public:
    explicit charge(std::uint32_t entity_id);
    bitmap_key get_bitmap_key() const override {
        return "charge";
    }

    DEFINE_DESC_ONE(charge, damage)

private:
    void use(std::uint32_t index_on) override;

    std::int32_t damage{13};
    bool used{false};
    bool exhausted{false};
};

#endif //PIGEONWAR_CHARGE_H
