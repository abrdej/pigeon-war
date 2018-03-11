#include "death_mark.h"
#include "sender.h"
#include "common/animations.h"
#include "core/board.h"
#include "components/applied_effects.h"
#include "components/damage_taker.h"

death_mark::death_mark(std::uint32_t entity_id) : entity_id(entity_id) {

}

death_mark::~death_mark() {
	if (!mark_removed && enemy_id != std::numeric_limits<std::uint32_t>::max()) {
		remove_effect(enemy_id, "death_mark");
	}
}

void death_mark::use(std::uint32_t index_on) {

//	if (used)
//		return;
//
//	sender::send(make_action_message("death_mark, index_on);
//
//	enemy_id = board::at(index_on);
//
//	auto death_mark_receiver = make_after_n_round_callback_holder(death_mark_duration,
//																  [this]() {
//		remove_effect(enemy_id, "death_mark");
//		mark_removed = true;
//
//		set_damage_receiver(entity_id, entity_manager::get(entity_id).get<damage_taker>()->get_damage_receiver());
//	});
//
//	add_effect(enemy_id,
//				  "death_mark",
//				  std::move(death_mark_receiver));
//
//	set_damage_receiver(entity_id, [this](health_field& health_pack, const damage_pack& dmg) mutable {
//
//		auto has_death_mark = has_effect(dmg.damage_dealer_id, "death_mark");
//
//		if (has_death_mark) {
//			return 0;
//
//		} else {
//			auto final_damage = std::min(health_pack.health, dmg.damage_value);
//			health_pack.health -= final_damage;
//
//			return final_damage;
//		}
//	});
//
//	used = true;
}