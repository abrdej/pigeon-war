#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "managers/managers.h"

class healths_manager : public base_manager<int, int>
{
	static inline int calculate_damage(size_t entity_id, int damage)
	{
		return damage;
	}
public:
	static inline int receive_damage(size_t entity_id, int damage)
	{
		auto& health = component_reference_for(entity_id);
		auto final_damage = std::min(health, calculate_damage(entity_id, damage));
		health -= final_damage;
		return final_damage;
	}
	static bool is_destructible(size_t entity_id) {
		auto& health = component_reference_for(entity_id);
		return health != indestructible;
	}
};

#endif