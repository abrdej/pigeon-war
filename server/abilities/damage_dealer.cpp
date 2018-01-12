#include "damage_dealers.h"
#include "managers/entity_manager.h"
#include <random>

namespace damage_dealers {

sf::Int32 random_damage(sf::Int32 damage)
{
	//auto dist = static_cast<sf::Int32>(std::round(damage * 0.2f));

	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<sf::Int32> uniform_dist(-1, 1);
	sf::Int32 random = uniform_dist(dre);
	return damage + random;
}

}


sf::Int32 damage_dealers::standard_damage_dealer(const damage_pack& dmg)
{
	if (!healths_manager::is_destructible(dmg.damage_receiver_id)) {
		return 0;
	}

	damage_pack dmg_up = dmg;

	dmg_up.damage_value = random_damage(dmg.damage_value);
	auto dealt_damage = healths_manager::receive_damage(dmg_up);

	auto&& health_pack = healths_manager::component_for(dmg.damage_receiver_id);
	if (health_pack.health <= 0 && health_pack.is_destructible)
		entity_manager::destroy(dmg.damage_receiver_id);

	return dealt_damage;
}