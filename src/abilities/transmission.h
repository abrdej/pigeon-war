//
// Created by abrdej on 02.04.18.
//

#ifndef PIGEONWAR_TRANSMISSION_H
#define PIGEONWAR_TRANSMISSION_H

#include "path_target_ability.h"

class transmission final : public path_target_ability<4>
{
public:
    explicit transmission(std::uint32_t entity_id);
    bitmap_key get_bitmap_key() const override {
        return "transmission";
    }

    DEFINE_DESC_ZERO(transmission)

private:
    void use(std::uint32_t from_index) override;
    void transmit(std::uint32_t to_index);

private:
    std::uint32_t entity_id;
    bool used{false};
    std::uint32_t from_index;
};

#endif //PIGEONWAR_TRANSMISSION_H
