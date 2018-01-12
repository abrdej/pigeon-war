#include "death_mark.h"
#include "sender.h"
#include "common/animations.h"
#include "core/board.h"
#include "managers/additions_manager.h"
#include "managers/health_manager.h"

death_mark::death_mark(sf::Uint64 entity_id) : entity_id(entity_id) {

}

death_mark::~death_mark() {
	if (!mark_removed) {
		additions_manager::remove_component(enemy_id,
											"death_mark");
	}
}

void death_mark::use(sf::Uint64 index_on) {

	if (used)
		return;

	sender::send(message_types::animation, animation_def::death_mark, index_on);

	enemy_id = board::at(index_on);

	auto death_mark_receiver =
			turn::turn_system::every_turn([this, counter = 0]() mutable {
				if (counter++ == death_mark_duration * 2) {
					additions_manager::remove_component(enemy_id,
														"death_mark");
					mark_removed = true;

					healths_manager::set_damage_receiver(entity_id, healths_manager::damage_receiver());
				}
			});

	additions_manager::add_component(enemy_id,
									 "death_mark",
									 death_mark_receiver);

	healths_manager::set_damage_receiver(entity_id, [this](health_field& health_pack, const damage_pack& dmg) mutable {

		auto has_death_mark = additions_manager::has_component(dmg.damage_dealer_id, "death_mark");

		if (has_death_mark) {
			return 0;

		} else {
			auto final_damage = std::min(health_pack.health, dmg.damage_value);
			health_pack.health -= final_damage;

			return final_damage;
		}
	});

	used = true;
}