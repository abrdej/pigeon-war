//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_PROTECTION_FIELD_H
#define PIGEONWAR_PROTECTION_FIELD_H

#include <core/turn_system.h>
#include "straight_target_ability.h"

class protection_field : public straight_target_ability<3>, protected turn_events_helper::every_turn_callback_helper {
public:
    explicit protection_field(std::uint64_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::protection_field;
	}

	bool active() const {
		return is_active;
	}

private:
    void use(std::uint64_t index_on) override;
    bool is_active{true};
    bool used{false};
    const std::int32_t damage = 16;
};

#endif //PIGEONWAR_PROTECTION_FIELD_H
