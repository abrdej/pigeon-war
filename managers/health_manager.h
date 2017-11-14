#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "managers/managers.h"

struct health_field {
	int health;
	int base_health;
};

static const int indestructible = std::numeric_limits<int>::max();

class healths_manager : public base_manager<health_field, health_field>
{
	static inline int calculate_damage(size_t entity_id, int damage)
	{
		return damage;
	}
public:
	static inline void add_component(size_t entity_id, const managed_component_type& component)
	{
		managed_component_type health_component = component;
		health_component.health = health_component.base_health;
		base_manager<health_field, health_field>::add_component(entity_id, health_component);
	}
	static inline int receive_damage(size_t entity_id, int damage)
	{
		auto& health_pack = component_reference_for(entity_id);
		auto final_damage = std::min(health_pack.health, calculate_damage(entity_id, damage));
		health_pack.health -= final_damage;
		return final_damage;
	}
	static bool is_destructible(size_t entity_id) {
		auto& health_pack = component_reference_for(entity_id);
		return health_pack.base_health != indestructible;
	}
};

#endif