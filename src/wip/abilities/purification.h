//
// Created by abrdej on 06.02.18.
//

#ifndef PIGEONWAR_PURIFICATION_H
#define PIGEONWAR_PURIFICATION_H

#include <turn_based/path_target_ability.h>
#include <turn_based/per_turn_usable.h>

class purification : public path_target_ability,
                     per_turn_usable {
public:
    explicit purification(std::uint32_t entity_id);

    bitmap_key get_name() const override {
        return "purification";
    }

    DEFINE_DESC_ONE(purification, power_cost)

private:
    void use(std::uint32_t index_on) override;

    std::uint32_t entity_id;
    std::int32_t power_cost{12};
};

#endif //PIGEONWAR_PURIFICATION_H
