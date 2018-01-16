#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "entities/entity.h"
#include "server/abilities/abilities.h"
#include "abilities_manager.h"
#include "health_manager.h"
#include "name_field.h"
#include "abilities_manager.h"
#include <functional>
#include <gui/drawing_manager.h>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include "entity_remover.h"
#include "core/board.h"

class entity_manager final
{
	static std::unordered_map<std::uint64_t, base_entity> entities;

	static std::vector<std::function<void(std::uint64_t)>> on_destroy_callbacks;

	inline static std::uint64_t generate_id() {
		static std::uint64_t entity_id_generator = 0;
		return entity_id_generator++;
	}

public:
	template <typename EntityFactory>
	inline static std::uint64_t create()
	{
		auto entity_id = generate_id();

		entities.emplace(entity_id, EntityFactory::create(entity_id));

		return entity_id;
	}
	static base_entity get(std::uint64_t entity_id) {
		return entities.at(entity_id);
	}
	inline static bool alive(std::uint64_t entity_id)
	{
		return entities.find(entity_id) != std::end(entities);
	}
	inline static void destroy(std::uint64_t entity_id)
	{
		entities.erase(entity_id);

		board::remove_entity(entity_id);

		call_destroy_callbacks(entity_id);
	}
	static void on_destroy(const std::function<void(std::uint64_t)>& callback)
	{
		on_destroy_callbacks.push_back(callback);
	}
	static void call_destroy_callbacks(std::uint64_t entity_id)
	{
		for (auto& callback : on_destroy_callbacks)
			callback(entity_id);
	}
};

#endif