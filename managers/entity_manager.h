#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "entities/entity.h"
#include "abilities/abilities.h"
#include "abilities_manager.h"
#include "health_manager.h"
#include "names_manager.h"
#include "managers/abilities_manager.h"
#include <functional>
#include <gui/drawing_manager.h>
#include <entities/wretch.h>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <entities/shooter.h>
#include "directions_manager.h"
#include "types_manager.h"
#include "ai/ai_manager.h"
#include "entity_remover.h"
#include "core/board.h"

template <typename... T>
void add_components(std::size_t entity_id, const std::tuple<T...>& tuple) {
	int t[] = {(add_component_of_type(entity_id, std::get<T>(tuple)), 0)...};
}

class entity_manager final
{
	static std::unordered_set<size_t> entities_;
	static std::vector<std::function<void(size_t)>> on_destroy_callbacks_;

	inline static size_t generate_id() {
		static size_t entity_id_generator = 0;
		return entity_id_generator++;
	}

public:
	template <typename EntityComponents>
	inline static size_t create()
	{
		auto entity_id = generate_id();

		entities_.insert(entity_id);

		auto components = EntityComponents::create(entity_id);
		add_components(entity_id, components);

		return entity_id++;
	}
	inline static bool alive(size_t entity_id)
	{
		return entities_.find(entity_id) != std::end(entities_);
	}
	inline static void destroy(size_t entity_id)
	{
		entities_.erase(entity_id);

        entity_remover::remove(entity_id);

		board::remove_entity(entity_id);

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