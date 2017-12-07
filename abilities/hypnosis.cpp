#include <core/states.h>
#include <core/board.h>
#include <managers/additions_manager.h>
#include <managers/abilities_manager.h>
#include <managers/entity_manager.h>
#include "hypnosis.h"
#include "abilities.h"

hypnosis_effect::hypnosis_effect(std::size_t receiver_entity_id) {

//	auto& abilities = abilities_manager::component_for(receiver_entity_id);
//	abilities.is_active = false;
//
//	rec = turn::turn_system::every_turn([this, receiver_entity_id, counter = 0]() mutable {
//
//		if (entity_manager::alive(receiver_entity_id)) {
//			if (++counter == 2) {
//
//				auto& inner_abilities = abilities_manager::component_for(receiver_entity_id);
//				inner_abilities.is_active = true;
//
//				rec.reset();
//				destroyer();
//			}
//
//		} else {
//			rec.reset();
//			destroyer();
//		}
//	});
}

hypnosis::hypnosis() {

}

void hypnosis::prepare(size_t for_index) {

	states::state_controller::selected_index_ = for_index;

	path_finder path_finder(true);
	path_finder.calc(for_index);
	path_finder.get_possible_movements(states::state_controller::possible_movements_,
									   states::state_controller::possible_movements_costs_,
									   range);

	states::state_controller::actual_targeting_type_ = states::target_types::enemy;
	states::state_controller::wait_for_action([this](size_t index)
											  {
												  return use(index);
											  });
}

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
	animation::player<animation::flash_bitmap>::launch(animation::flash_bitmap(to_index,
																			   std::chrono::milliseconds(150),
																			   "field_shoot.png"));
	animation::base_player::play();
}