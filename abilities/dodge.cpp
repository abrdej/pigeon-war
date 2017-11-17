#include "dodge.h"
#include "managers/health_manager.h"
#include <iostream>
#include <animation/animation.h>
#include <core/board.h>

dodge::dodge(std::size_t entity_id) {

	healths_manager::set_damage_receiver(entity_id, [this, entity_id, counter = 0](health_field& health_pack, int damage) mutable {

		std::cout << "my damage receiver\n";

		if (++counter == 3) {

			counter = 0;

			auto index = board::index_for(entity_id);

			auto backup_id = board::take(index);
			animation::player<animation::flash_bitmap>::launch(
					animation::flash_bitmap(index,
											std::chrono::milliseconds(150),
											"dodge.png"));
			animation::base_player::play();

			board::give_back(backup_id, index);

			return 0;

		} else {
			auto final_damage = std::min(health_pack.health, damage);
			health_pack.health -= final_damage;

			return final_damage;
		}
	});
}