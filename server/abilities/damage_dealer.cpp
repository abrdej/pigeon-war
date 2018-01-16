#include "damage_dealers.h"
#include "managers/entity_manager.h"
#include <random>
#include "entities/entity.h"
#include "damage_taker.h"

std::int32_t random_damage(std::int32_t damage) {
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<std::int32_t> uniform_dist(-1, 1);
	std::int32_t random = uniform_dist(dre);
	return damage + random;
}


//sf::Int32 damage_dealers::standard_damage_dealer(const damage_pack& dmg)
//{
//	if (!healths_manager::is_destructible(dmg.damage_receiver_id)) {
//		return 0;
//	}
//
//	damage_pack dmg_up = dmg;
//
//	dmg_up.damage_value = random_damage(dmg.damage_value);
//	auto dealt_damage = healths_manager::receive_damage(dmg_up);
//
//	auto&& health_pack = healths_manager::component_for(dmg.damage_receiver_id);
//	if (health_pack.health <= 0 && health_pack.is_destructible)
//		entity_manager::destroy(dmg.damage_receiver_id);
//
//	return dealt_damage;
//}

std::int32_t damage_dealers::standard_damage_dealer(const damage_pack& dmg)
{
	base_entity entity = entity_manager::get(dmg.damage_receiver_id);

	auto health_field_ptr = entity.get<health_field>();

	if (!health_field_ptr->is_destructible) {
		return 0;
	}

	damage_pack dmg_up = dmg;
	dmg_up.damage_value = random_damage(dmg.damage_value);

	auto dealt_damage = entity.get<damage_taker>()->receive_damage(dmg);


	if (health_field_ptr->health <= 0 && health_field_ptr->is_destructible)
		entity_manager::destroy(dmg.damage_receiver_id);

	return dealt_damage;
}