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
    explicit spider_web(sf::Uint64 entity_id);

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::spider_web;
	}

	void set_used();

private:
    void use(sf::Uint64 index_on) override;

private:
    sf::Uint64 caster_id;
    sf::Int32 damage = 6;
};

#endif //PIGEONWAR_SPIDER_WEB_H
