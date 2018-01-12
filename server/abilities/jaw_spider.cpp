#include <core/states_controller.h>
#include <core/board.h>
#include <managers/health_manager.h>
#include <managers/abilities_manager.h>
#include <managers/additions_manager.h>
#include "jaw_spider.h"
#include "damage_dealers.h"
#include "spider_web.h"

void jaw_spider::use(sf::Uint64 index_on) {

	if (used) {
		return;
	}

	auto used_from_index = states::state_controller::selected_index_;
	auto caster_id = board::at(used_from_index);

	sender::send(message_types::animation, animation_def::jaw_spider, index_on);

	auto enemy_id = board::at(index_on);

	auto has_spider_web_effect = additions_manager::has_component(enemy_id, "spider_web_effect");

	auto final_damage = has_spider_web_effect ? damage + bonus_for_spider_web_effect : damage;

	damage_dealers::standard_damage_dealer(melee_damage(final_damage, enemy_id, caster_id));

	used = true;

	auto& abilities = abilities_manager::component_for(caster_id);
	auto spider_web_ptr = std::static_pointer_cast<spider_web>(abilities.type(abilities::ability_types::special));
	spider_web_ptr->set_used();
}

void jaw_spider::set_used() {
	used = true;
}