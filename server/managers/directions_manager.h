#ifndef DIRECTIONS_MANAGER_H
#define DIRECTIONS_MANAGER_H

#include "common/managers.h"
#include "entities/entity.h"

class directions_manager : public base_manager<directions, directions&>
{
public:
	static inline void turn_left(sf::Uint64 entity_id)
	{
		component_for(entity_id) = directions::left;
	}
	static inline void turn_right(sf::Uint64 entity_id)
	{
		component_for(entity_id) = directions::right;
	}
};

template <>
inline void add_component_of_type<directions>(sf::Uint64 entity_id, const directions& component) {
	directions_manager::add_component(entity_id, component);
}



#endif