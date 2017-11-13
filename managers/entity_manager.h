#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "entities/entity.h"
#include "abilities/abilities.h"
#include "abilities/damage_receivers.h"
#include "health_component.h"
#include "names_manager.h"
#include "managers/abilities_manager.h"
#include <functional>
#include "directions_manager.h"
#include "types_manager.h"
#include "ai/ai_manager.h"
#include "entity_remover.h"

class entity_manager final
{
	static std::unordered_set<size_t> entities_;
	static size_t next_;
	static std::vector<std::function<void(size_t)>> on_destroy_callbacks_;
public:
	inline static size_t add(entity_data entity_data)
	{
		++next_;
		while (alive(next_))
			++next_;
		entities_.insert(next_);

		types_manager::add_component(next_, entity_data.type);
		healths_manager::add_component(next_, entity_data.health);
		names_manager::add_component(next_, entity_data.name);
		abilities_manager::add_component(next_, entity_data.entity_abilities);
		directions_manager::add_component(next_, entity_data.direction);

		return next_;
	}
	inline static bool alive(size_t entity_id)
	{
		return entities_.find(entity_id) != std::end(entities_);
	}
	inline static void destroy(size_t entity_id)
	{
		entities_.erase(entity_id);

        entity_remover::remove(entity_id);

		call_destroy_callbacks(entity_id);
	}
	static void on_destroy(const std::function<void(size_t)>& callback)
	{
		on_destroy_callbacks_.push_back(callback);
	}
	static void call_destroy_callbacks(size_t entity_id)
	{
		for (auto& callback : on_destroy_callbacks_)
			callback(entity_id);
	}
};

#endif