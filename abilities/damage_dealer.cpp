#include "damage_dealers.h"
#include "managers/entity_manager.h"
#include "animation/animation.h"
#include <random>

namespace damage_dealers
{
int random_damage(int damage)
{
	auto dist = static_cast<int>(std::round(damage * 0.2f));

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> uniform_dist(-dist, dist);
	int random = uniform_dist(dre);
	return damage + random;
}

void play_change_health_animation(size_t to_index, int change_health)
{
	animation::player<animation::change_health>::launch(animation::change_health(to_index,
																				 change_health));
	animation::base_player::play();
}

int standard_damage_dealer(int damage, size_t to_index)
{
	auto enemy_id = board::at(to_index);

	if (!healths_manager::is_destructible(enemy_id)) {
		return 0;
	}

	auto rand_damage = random_damage(damage);
	auto dealt_damage = healths_manager::receive_damage(enemy_id, rand_damage);

	play_change_health_animation(to_index, -dealt_damage);

	if (healths_manager::component_for(enemy_id).health <= 0)
		entity_manager::destroy(enemy_id);

	return dealt_damage;
}
};