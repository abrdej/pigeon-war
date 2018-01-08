#include <core/states_controller.h>
#include <core/board.h>
#include <managers/additions_manager.h>
#include <managers/abilities_manager.h>
#include <managers/entity_manager.h>
#include "hypnosis.h"

void hypnosis::use(size_t index_on) {

	if (used)
		return;

	play_animation(index_on);

	auto enemy_id = board::at(index_on);

	auto& abilities = abilities_manager::component_for(enemy_id);
	abilities.is_active = false;

	auto hypnosis_receiver = turn::turn_system::every_turn([this, enemy_id, counter = 0]() mutable {
		if (++counter == 2) {

			auto& inner_abilities = abilities_manager::component_for(enemy_id);
			inner_abilities.is_active = true;

			additions_manager::remove_component(enemy_id,
												"hypnosis");
		}
	});

	additions_manager::add_component(enemy_id, "hypnosis", hypnosis_receiver);

	used = true;
}

void hypnosis::play_animation(size_t to_index) {
	animations_queue::push_animation(animation_types::flash_bitmap,
									 to_index,
									 150,
									 0,
									 bitmap_key::field_shoot);
}