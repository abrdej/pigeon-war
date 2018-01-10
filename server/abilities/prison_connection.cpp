#include "prison_connection.h"
#include "managers/additions_manager.h"
#include "core/board.h"
#include "damage_dealers.h"

prison_connection::prison_connection(std::size_t entity_id) : entity_id(entity_id) {

}

void prison_connection::use(size_t index_on) {

	auto enemy_id = board::at(index_on);

	auto prison_connection_receiver =
			turn::turn_system::every_turn([this, enemy_id, counter = 0, end_duration = duration]() mutable {

				if (counter++ % 2) {
					//damage_dealers::standard_damage_dealer(special_damage(final_damage, enemy_id));

					//std::cout << "final_damage: " << final_damage << "\n";

					if (counter == end_duration * 2) {
						additions_manager::remove_component(enemy_id,
															"prison_connection_effect");
						entities_with_effect.erase(std::remove(std::begin(entities_with_effect), std::end(entities_with_effect), enemy_id),
												   std::end(entities_with_effect));
					}
				}
			});

	additions_manager::add_component(enemy_id, "prison_connection_effect", prison_connection_receiver);
	entities_with_effect.push_front(enemy_id);

	int number_of_entities_with_effect = static_cast<int>(entities_with_effect.size());

	final_damage = base_damage + number_of_entities_with_effect * damage_per_entities_with_effect;

	std::cout << "final_damage: " << final_damage << "\n";

	animations_queue::push_animation(animation_types::change_bitmap,
									 entity_id,
									 0,
									 0,
									 bitmap_key::sorcerer_attack);

	for (auto&& entity_with_effect : entities_with_effect) {
		auto index = board::index_for(entity_with_effect);

		sender::send(message_types::animation, animation_def::prison_connection, index);

		damage_dealers::standard_damage_dealer(magic_damage(final_damage, board::at(index), entity_id));
	}

	animations_queue::push_animation(animation_types::change_bitmap,
									 entity_id,
									 0,
									 0,
									 bitmap_key::sorcerer);
}