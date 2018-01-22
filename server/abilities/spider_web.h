//
// Created by abrde on 05.12.2017.
//

#ifndef PIGEONWAR_SPIDER_WEB_H
#define PIGEONWAR_SPIDER_WEB_H

#include "straight_target_ability.h"
#include "per_turn_usable.h"

class spider_web final : public straight_target_ability<5>, per_turn_usable
{
public:
    explicit spider_web(std::uint32_t entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::spider_web;
	}

	void set_used();

private:
    void use(std::uint32_t index_on) override;

private:
    std::uint32_t caster_id;
    std::int32_t damage = 6;
	std::int32_t duration = 3;
};

#endif //PIGEONWAR_SPIDER_WEB_H
