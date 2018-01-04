//
// Created by abrde on 03.12.2017.
//

#ifndef PIGEONWAR_PROTECTION_FIELD_H
#define PIGEONWAR_PROTECTION_FIELD_H

#include <core/turn.h>
#include "ability.h"

class protection_field : public ability, protected turn_events_helper::every_turn_callback_helper {
public:
    explicit protection_field(std::size_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::protection_field;
	}

	bool active() const {
		return is_active;
	}

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);
    void play_animation(size_t from_index, size_t to_index);
    bool is_active{true};
    bool used{false};
    const int range = 3;
    const int damage = 16;
};

#endif //PIGEONWAR_PROTECTION_FIELD_H