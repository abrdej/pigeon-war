#include "health_manager.h"

std::unordered_map<sf::Uint64, healths_manager::damage_receiver> healths_manager::damage_receivers;

std::unordered_map<sf::Uint64, std::unordered_map<sf::Uint64, std::function<void(const damage_pack&)>>>
		healths_manager::on_receive_damage_before_callbacks;

std::unordered_map<sf::Uint64, std::unordered_map<sf::Uint64, std::function<void(const damage_pack&)>>>
		healths_manager::on_receive_damage_after_callbacks;


void play_change_health_animation(sf::Uint64 to_index, sf::Int32 change_health)
{
	animations_queue::push_animation(animation_types::change_health,
									 to_index,
									 change_health,
									 0,
									 bitmap_key::none);
	animations_queue::pull();

	sender::send(message_types::healths, healths_manager::get_map());
}