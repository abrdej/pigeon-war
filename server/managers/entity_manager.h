#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "entities/entity.h"
#include "core/board.h"

class entity_manager final
{
	static std::unordered_map<std::uint64_t, base_entity> entities;

	static std::unordered_map<std::uint64_t, std::vector<std::function<void()>>> on_destroy_callbacks;

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
	static void on_destroy(std::uint64_t entity_id, const std::function<void()>& callback)
	{
		on_destroy_callbacks[entity_id].push_back(callback);
	}
	static void call_destroy_callbacks(std::uint64_t entity_id)
	{
		for (auto& callback : on_destroy_callbacks[entity_id])
			callback();
	}
	template <typename Function>
	static void for_all(Function function) {
		for (auto&& entity_pack : entities) {
			function(entity_pack.second);
		}
	}
};

#endif