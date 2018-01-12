#ifndef MANAGERS_H
#define MANAGERS_H

#include <unordered_map>
#include <vector>
#include <type_traits>
#include "server/managers/entity_remover.h"

template <typename T, typename R>
class base_manager
{
protected:
	using managed_component_type = T;
	using return_component_type = R;

	static std::unordered_map<sf::Uint64, managed_component_type> map_;

public:
	static inline void add_component(sf::Uint64 entity_id, const managed_component_type& component)
	{
		map_.emplace(entity_id, component);
        entity_remover::add_remover(entity_id, [entity_id](){
            map_.erase(entity_id);
        });
	}
	static inline bool has_component(sf::Uint64 entity_id)
	{
		auto it = map_.find(entity_id);
        return it != std::end(map_);
	}
	static inline return_component_type component_for(sf::Uint64 entity_id)
	{
        return map_.at(entity_id);
	}
protected:
	static inline managed_component_type& component_reference_for(sf::Uint64 entity_id)
	{
        return map_.at(entity_id);
	}
};

template <typename T, typename R>
std::unordered_map<sf::Uint64, T> base_manager<T, R>::map_;

template <typename T>
void add_component_of_type(sf::Uint64, const T&);

#endif