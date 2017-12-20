//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_SPIDER_WEB_H
#define PIGEONWAR_SPIDER_WEB_H

#include "ability.h"
#include "core/turn.h"

class spider_web final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
    explicit spider_web(std::size_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::spider_web;
	}

	void set_used();

private:
    void prepare(size_t for_index) override;
    void use(size_t index_on);

private:
    std::size_t caster_id;
    int range = 5;
    int damage = 6;
    bool used{false};
};

#endif //PIGEONWAR_SPIDER_WEB_H
