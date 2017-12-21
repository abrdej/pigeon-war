#include <core/states_controller.h>
#include <core/board.h>
#include <managers/health_manager.h>
#include <managers/abilities_manager.h>
#include <managers/additions_manager.h>
#include "jaw_spider.h"
#include "damage_dealers.h"
#include "spider_web.h"

jaw_spider::jaw_spider() {
	onEveryRound([this]() {
		used = false;
	});
}

void jaw_spider::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;
	board_helper::neighboring_fields(for_index, states::state_controller::possible_movements_, false);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

void jaw_spider::use(size_t index_on) {

	if (used) {
		return;
	}

	auto used_from_index = states::state_controller::selected_index_;
	auto caster_id = board::at(used_from_index);

	play_animation(index_on);

	auto enemy_id = board::at(index_on);

	auto has_spider_web_effect = additions_manager::has_component(enemy_id, "spider_web_effect");

	auto final_damage = has_spider_web_effect ? damage + bonus_for_spider_web_effect : damage;

	damage_dealers::standard_damage_dealer(melee_damage(final_damage, enemy_id, caster_id));

	used = true;

	auto& abilities = abilities_manager::component_for(caster_id);
	auto spider_web_ptr = std::static_pointer_cast<spider_web>(abilities.type(abilities::ability_types::special));
	spider_web_ptr->set_used();
}

void jaw_spider::play_animation(size_t index_on) {
	animations_queue::push_animation(animation_types::flash_bitmap,
									 index_on,
									 150,
									 0,
									 bitmap_key::jaw_spider);
}

void jaw_spider::set_used() {
	used = true;
}