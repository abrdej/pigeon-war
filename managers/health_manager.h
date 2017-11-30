#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "managers/managers.h"
#include <limits>
#include <algorithm>

struct health_field {
	int health;
	int base_health;
	bool is_destructible{true};
};

static const int indestructible = std::numeric_limits<int>::max();

class healths_manager : public base_manager<health_field, health_field>
{
	struct damage_receiver {
		damage_receiver() {
			impl = [](health_field& health_pack, int damage) {

				auto final_damage = (std::min)(health_pack.health, damage);
				health_pack.health -= final_damage;

				return final_damage;
			};
		}
		template <typename Callback>
		damage_receiver(Callback callback) : impl(callback) {
		}
		template <typename Callback>
		damage_receiver& operator=(Callback callback) {
			impl = callback;
			return *this;
		}
		int operator()(health_field& entity_id, int damage) {
			return impl(entity_id, damage);
		}
		std::function<int(health_field&, int)> impl;
	};

	static std::unordered_map<size_t, std::vector<std::function<void()>>> on_receive_damage_callbacks;

	static std::unordered_map<size_t, damage_receiver> damage_receivers;

public:
	static inline void add_component(size_t entity_id, const managed_component_type& component)
	{
		managed_component_type health_component = component;
		health_component.health = health_component.base_health;
		base_manager<health_field, health_field>::add_component(entity_id, health_component);
	}
	static inline int receive_damage(size_t entity_id, int damage)
	{
		for (auto&& callback : on_receive_damage_callbacks[entity_id]) {
			callback();
		}

		auto& health_pack = healths_manager::component_reference_for(entity_id);
		return damage_receivers[entity_id](health_pack, damage);
	}
	static bool is_destructible(size_t entity_id) {
		auto& health_pack = component_reference_for(entity_id);
		return health_pack.is_destructible;
	}
	static void set_destructible(size_t entity_id, bool value) {
		auto& health_pack = component_reference_for(entity_id);
		health_pack.is_destructible = value;
	}

	template <typename DamageReceiver>
	static void set_damage_receiver(size_t entity_id, DamageReceiver damage_receiver) {
		damage_receivers[entity_id] = damage_receiver;
	}

	template <typename Callback>
	static void on_receive_damage(size_t entity_id, Callback callback) {
		on_receive_damage_callbacks[entity_id].push_back(callback);
	}

	//friend class DamageReceiver;
};

#endif