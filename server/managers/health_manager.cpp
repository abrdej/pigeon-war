#include "health_manager.h"

std::unordered_map<size_t, healths_manager::damage_receiver> healths_manager::damage_receivers;

std::unordered_map<std::size_t, std::unordered_map<std::size_t, std::function<void(const damage_pack&)>>>
		healths_manager::on_receive_damage_before_callbacks;

std::unordered_map<std::size_t, std::unordered_map<std::size_t, std::function<void(const damage_pack&)>>>
		healths_manager::on_receive_damage_after_callbacks;


void play_change_health_animation(size_t to_index, int change_health)
{
	animations_queue::push_animation(animation_types::change_health,
									 to_index,
									 change_health,
									 0,
									 bitmap_key::none);
	animations_queue::pull();

	sender::send(message_types::healths, healths_manager::get_map());
}