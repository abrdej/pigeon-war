#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "common/managers.h"
#include "modifications_manager.h"
#include <limits>
#include <algorithm>
#include <core/board.h>
#include <common/health_field.h>
#include <common/animations.h>
#include <core/states_controller.h>
#include <core/animations_queue.h>
#include <sender.h>
#include "damage_pack.h"


inline damage_pack melee_damage(sf::Int32 value, sf::Uint64 receiver_id, sf::Uint64 dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::MELEE, receiver_id, dealer_id};
}

inline damage_pack ranged_damage(sf::Int32 value, sf::Uint64 receiver_id, sf::Uint64 dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::RANGED, receiver_id, dealer_id};
}

inline damage_pack magic_damage(sf::Int32 value, sf::Uint64 receiver_id, sf::Uint64 dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::MAGIC, receiver_id, dealer_id};
}

inline damage_pack special_damage(sf::Int32 value, sf::Uint64 receiver_id, sf::Uint64 dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::SPECIAL, receiver_id, dealer_id};
}

inline damage_pack healing(sf::Int32 value, sf::Uint64 receiver_id) {
	return damage_pack{-value, damage_types::UNDEFINED, receiver_id, no_damage_dealer};
}

void play_change_health_animation(sf::Uint64 to_index, sf::Int32 change_health);

class healths_manager : public base_manager<health_field, health_field>
{
public:
	struct damage_receiver {
		damage_receiver() {
			impl = [](health_field& health_pack, const damage_pack& dmg) {

				auto final_damage = (std::min)(health_pack.health, dmg.damage_value);

				health_pack.health -= final_damage;

				return final_damage;
			};
		}
		template <typename Callback>
		explicit damage_receiver(Callback callback) : impl(callback) {
		}
		template <typename Callback>
		damage_receiver& operator=(Callback callback) {
			impl = callback;
			return *this;
		}
		operator std::function<sf::Int32(health_field&, const damage_pack&)>() {
			return impl;
		}
		sf::Int32 operator()(health_field& entity_id, const damage_pack& dmg) {
			return impl(entity_id, dmg);
		}
		std::function<sf::Int32(health_field&, const damage_pack&)> impl;
	};

public:
	enum class on_receive_damage_policy {
		before,
		after
	};

private:
	static std::unordered_map<sf::Uint64, std::unordered_map<sf::Uint64, std::function<void(const damage_pack&)>>>
			on_receive_damage_before_callbacks;

	static std::unordered_map<sf::Uint64, std::unordered_map<sf::Uint64, std::function<void(const damage_pack&)>>>
			on_receive_damage_after_callbacks;

	static std::unordered_map<sf::Uint64, damage_receiver> damage_receivers;

public:

	static std::unordered_map<sf::Uint64, sf::Int32> get_map() {
		std::unordered_map<sf::Uint64, sf::Int32> returned_map;

		for (auto&& elem : map_) {
			returned_map.insert(std::make_pair(elem.first, elem.second.health));
		}

		return std::move(returned_map);
	}

	static inline void add_component(sf::Uint64 entity_id, const managed_component_type& component)
	{
		managed_component_type health_component = component;
		health_component.health = health_component.base_health;
		base_manager<health_field, health_field>::add_component(entity_id, health_component);

		entity_remover::add_remover(entity_id, [entity_id]() {
			damage_receivers.erase(entity_id);
			on_receive_damage_before_callbacks.erase(entity_id);
			on_receive_damage_after_callbacks.erase(entity_id);
		});
	}
	static inline sf::Int32 receive_damage(const damage_pack& dmg)
	{
		damage_pack damage_pack = dmg;
		damage_pack.damage_value += modifications_manager::damage_receiver_modifier_value(dmg.damage_receiver_id);

		for (auto&& callback_pack : on_receive_damage_before_callbacks[damage_pack.damage_receiver_id]) {
			callback_pack.second(damage_pack);
		}

		auto& health_pack = component_reference_for(damage_pack.damage_receiver_id);
		auto received_damage = damage_receivers[damage_pack.damage_receiver_id](health_pack, damage_pack);

		auto enemy_index = board::index_for(damage_pack.damage_receiver_id);
		play_change_health_animation(enemy_index, -received_damage);

		for (auto&& callback_pack : on_receive_damage_after_callbacks[damage_pack.damage_receiver_id]) {
			callback_pack.second(damage_pack);
		}

		return received_damage;
	}
	static bool is_destructible(sf::Uint64 entity_id) {
		auto& health_pack = component_reference_for(entity_id);
		return health_pack.is_destructible;
	}
	static void set_destructible(sf::Uint64 entity_id, bool value) {
		auto& health_pack = component_reference_for(entity_id);
		health_pack.is_destructible = value;
	}

	template <typename DamageReceiver>
	static void set_damage_receiver(sf::Uint64 entity_id, DamageReceiver damage_receiver) {
		damage_receivers[entity_id] = damage_receiver;
	}
	static std::function<sf::Int32(health_field&, const damage_pack&)> get_damage_receiver(sf::Uint64 entity_id) {
		return damage_receivers[entity_id];
	}

	template <typename Callback>
	static sf::Uint64 on_receive_damage(sf::Uint64 entity_id, Callback callback, const on_receive_damage_policy& policy) {
//		on_receive_damage_callbacks[entity_id].push_back(std::make_pair(policy, callback));

		static std::unordered_map<sf::Uint64, sf::Uint64> id_gen;

		if (policy == on_receive_damage_policy::before) {
			auto callback_id = id_gen[entity_id]++;
			on_receive_damage_before_callbacks[entity_id].emplace(callback_id, callback);
			return callback_id;

		} else {
			auto callback_id = id_gen[entity_id]++;
			on_receive_damage_after_callbacks[entity_id].emplace(callback_id, callback);
			return callback_id;
		}
	}
	static void remove_on_receive_damage(sf::Uint64 entity_id, sf::Uint64 callback_id) {
		on_receive_damage_before_callbacks[entity_id].erase(callback_id);
		on_receive_damage_after_callbacks[entity_id].erase(callback_id);
	}
};

template <>
inline void add_component_of_type<health_field>(sf::Uint64 entity_id, const health_field& component) {
	healths_manager::add_component(entity_id, component);
}

#endif