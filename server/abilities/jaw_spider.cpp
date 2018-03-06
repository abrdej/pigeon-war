#include <core/states_controller.h>
#include <core/board.h>
#include <components/applied_effects.h>
#include <managers/entity_manager.h>
#include <common/make_message.h>
#include "jaw_spider.h"
#include "abilities.h"
#include "damage_dealers.h"
#include "spider_web.h"
#include "sender.h"
#include "common/animations.h"

void jaw_spider::use(std::uint32_t index_on) {

	if (used) {
		return;
	}

	auto used_from_index = states::state_controller::selected_index_;
	auto caster_id = board::at(used_from_index);

	sender::send(make_animation_message("jaw_spider", index_on));

	auto enemy_id = board::at(index_on);

	auto has_spider_web_effect = has_effect(enemy_id, "spider web");

	auto final_damage = has_spider_web_effect ? damage + bonus_for_spider_web_effect : damage;

	damage_dealers::standard_damage_dealer(melee_damage(final_damage, enemy_id, caster_id));

	used = true;

	auto abilities_ptr = entity_manager::get(caster_id).get<abilities>();

	auto spider_web_ptr = abilities_ptr->get<spider_web>();
	spider_web_ptr->set_used();
}

void jaw_spider::set_used() {
	used = true;
}