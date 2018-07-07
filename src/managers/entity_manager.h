#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <messages/make_message.h>
#include <sender.h>
#include "entities/entity.h"
#include "core/board.h"

class entity_manager final
{
	std::unordered_map<std::uint32_t, base_entity> entities;
	std::unordered_map<std::uint32_t, std::vector<std::function<void()>>> on_destroy_callbacks;

	inline std::uint32_t generate_id() {
		static std::uint32_t entity_id_generator = 0;
		return entity_id_generator++;
	}

public:
	template <typename EntityFactory>
	inline std::uint32_t create()
	{
		auto entity_id = generate_id();

		auto result = entities.emplace(entity_id, base_entity());
        result.first->second.entity_id = entity_id;
		EntityFactory::create(result.first->second);

		return entity_id;
	}
	base_entity get(std::uint32_t entity_id) {
		return entities.at(entity_id);
	}
	inline bool alive(std::uint32_t entity_id)
	{
		return entities.find(entity_id) != std::end(entities);
	}
	inline void destroy(std::uint32_t entity_id)
	{
		entities.erase(entity_id);

		//game::get<board>().remove_entity(entity_id);

		sender::send(make_remove_entity_message(entity_id));

		call_destroy_callbacks(entity_id);
	}
	void on_destroy(std::uint32_t entity_id, const std::function<void()>& callback)
	{
		on_destroy_callbacks[entity_id].push_back(callback);
	}
	void call_destroy_callbacks(std::uint32_t entity_id)
	{
		for (auto& callback : on_destroy_callbacks[entity_id])
			callback();
	}
	template <typename Function>
	void for_all(Function function) {
		for (auto&& entity_pack : entities) {
			function(entity_pack.second);
		}
	}
};

#endif