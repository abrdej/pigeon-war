//
// Created by abrde on 14.12.2017.
//

#ifndef PIGEONWAR_WRETCH_MOVING_H
#define PIGEONWAR_WRETCH_MOVING_H

#include "ability.h"
#include "core/turn_system.h"
#include "moveable.h"
#include <functional>

class wretch_moving final : public moveable_base, turn_callback_helper {
public:
    explicit wretch_moving(std::uint32_t entity_id);

    bitmap_key get_bitmap_key() const override {
        return bitmap_key::moveable;
    }

    void refresh_range() override {
        used = false;
    }

    bool has_range() const override {
        return !used;
    }

    void remove_range() override {
        used = true;
    }

    void set_slow_down(std::int32_t value) override {
        range = value;
    }
    void remove_slow_down() override {
        range = base_range;
    }

private:
    void prepare(std::uint32_t for_index) override;
    void move(std::uint32_t index_to);

private:
    std::uint32_t entity_id;
    std::int32_t max_range{4};
    std::int32_t range{4};
    std::int32_t base_range{4};
    const std::int32_t power_decrease_for_cost{2};
    bool used{false};
};


#endif //PIGEONWAR_WRETCH_MOVING_H
