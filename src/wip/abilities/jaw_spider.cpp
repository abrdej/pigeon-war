#include <turn_based/game_controller.h>
#include <turn_based/board.h>
#include <components/applied_effects.h>
#include <turn_based/managers/entity_manager.h>
#include <messages/massages_makers.h>
#include <jaw_spider.h>
#include <turn_based/abilities.h>
#include <turn_based/damage_dealers.h>
#include <spider_web.h>
#include <turn_based/sender.h>

void jaw_spider::use(std::uint32_t index_on) {

	if (used) {
		return;
	}

	auto used_from_index = game_control().selected_index_;
	auto caster_id = game_board().at(used_from_index);

	sender::send(make_action_message("jaw_spider", index_on));

	auto enemy_id = game_board().at(index_on);

	auto has_spider_web_effect = has_effect(enemy_id, "spider_web_slow");

	auto final_damage = has_spider_web_effect ? damage + bonus_for_spider_web_effect : damage;

	damage_dealers::standard_damage_dealer(melee_damage(final_damage, enemy_id, caster_id));

	used = true;

	auto abilities_ptr = game::get<entity_manager>().get(caster_id).get<abilities>();

	auto spider_web_ptr = abilities_ptr->get<spider_web>();
	spider_web_ptr->set_used();
}

void jaw_spider::set_used() {
	used = true;
}