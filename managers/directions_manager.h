#ifndef DIRECTIONS_MANAGER_H
#define DIRECTIONS_MANAGER_H

#include "managers.h"
#include <unordered_map>
#include <vector>
#include "entities/entity.h"

class directions_manager : public base_manager<entity_definition::directions, entity_definition::directions&>
{
public:
	static inline void turn_left(size_t entity_id)
	{
		component_for(entity_id) = entity_definition::directions::left;
	}
	static inline void turn_right(size_t entity_id)
	{
		component_for(entity_id) = entity_definition::directions::right;
	}
};



#endif