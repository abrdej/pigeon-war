#include "dodge.h"
#include "managers/health_manager.h"
#include <iostream>
#include <client/animation/animation.h>
#include <core/board.h>

dodge::dodge(std::size_t entity_id) {

	healths_manager::set_damage_receiver(entity_id, [this, entity_id, counter = 0](health_field& health_pack, const damage_pack& dmg) mutable {

		if (++counter == 3) {

			counter = 0;

			auto index = board::index_for(entity_id);

			auto backup_id = board::take(index);

			animations_queue::push_animation(animation_types::flash_bitmap, index, 150, 0, bitmap_key::dodge);

			board::give_back(backup_id, index);

			return 0;

		} else {
			auto final_damage = std::min(health_pack.health, dmg.damage_value);
			health_pack.health -= final_damage;

			return final_damage;
		}
	});
}