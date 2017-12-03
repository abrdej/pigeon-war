#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

#include "managers/managers.h"
#include <limits>
#include <algorithm>
#include <animation/animation.h>
#include <core/board.h>

struct health_field {
	int health;
	int base_health;
	bool is_destructible{true};
};

static const std::size_t no_damage_dealer = std::numeric_limits<std::size_t>::max();

enum class damage_types {
	MELEE,
	RANGED,
	MAGIC,
	SPECIAL,
	UNDEFINED
};

struct damage_pack {
	damage_pack(int value, damage_types type, std::size_t receiver_id)
			: damage_value(value),
              damage_receiver_id(receiver_id),
			  damage_type(type),
			  damage_dealer_id(no_damage_dealer) {}
	damage_pack(int value, damage_types type, std::size_t receiver_id, std::size_t dealer_id)
			: damage_value(value),
			  damage_type(type),
              damage_receiver_id(receiver_id),
			  damage_dealer_id(dealer_id) {}

	int damage_value;
	damage_types damage_type;
    std::size_t damage_receiver_id;
	std::size_t damage_dealer_id;
};

inline damage_pack melee_damage(int value, std::size_t receiver_id, std::size_t dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::MELEE, receiver_id, dealer_id};
}

inline damage_pack ranged_damage(int value, std::size_t receiver_id, std::size_t dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::RANGED, receiver_id, dealer_id};
}

inline damage_pack magic_damage(int value, std::size_t receiver_id, std::size_t dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::MAGIC, receiver_id, dealer_id};
}

inline damage_pack special_damage(int value, std::size_t receiver_id, std::size_t dealer_id = no_damage_dealer) {
	return damage_pack{value, damage_types::SPECIAL, receiver_id, dealer_id};
}

inline damage_pack healing(int value, std::size_t receiver_id) {
	return damage_pack{-value, damage_types::UNDEFINED, receiver_id, no_damage_dealer};
}

inline void play_change_health_animation(size_t to_index, int change_health)
{
	animation::player<animation::change_health>::launch(animation::change_health(to_index,
																				 change_health));
	animation::base_player::play();
}

static const int indestructible = std::numeric_limits<int>::max();

class healths_manager : public base_manager<health_field, health_field>
{
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
		int operator()(health_field& entity_id, const damage_pack& dmg) {
			return impl(entity_id, dmg);
		}
		std::function<int(health_field&, const damage_pack&)> impl;
	};

public:
	enum class on_receive_damage_policy {
		before,
		after
	};

private:
	static std::unordered_map<std::size_t,
            std::vector<std::pair<on_receive_damage_policy,
                    std::function<void(const damage_pack&)>>>> on_receive_damage_callbacks;

	static std::unordered_map<std::size_t, damage_receiver> damage_receivers;

public:
	static inline void add_component(std::size_t entity_id, const managed_component_type& component)
	{
		managed_component_type health_component = component;
		health_component.health = health_component.base_health;
		base_manager<health_field, health_field>::add_component(entity_id, health_component);

		// clean up receivers
		entity_remover::add_remover(entity_id, [entity_id]() {
			damage_receivers.erase(entity_id);
			on_receive_damage_callbacks.erase(entity_id);
		});
	}
	static inline int receive_damage(const damage_pack& dmg)
	{
		for (auto&& callback_pack : on_receive_damage_callbacks[dmg.damage_receiver_id]) {
			if (callback_pack.first == on_receive_damage_policy::before) {
				callback_pack.second(dmg);
			}
		}

		auto& health_pack = healths_manager::component_reference_for(dmg.damage_receiver_id);
		auto received_damage = damage_receivers[dmg.damage_receiver_id](health_pack, dmg);

		auto enemy_index = board::index_for(dmg.damage_receiver_id);
		play_change_health_animation(enemy_index, -received_damage);

		for (auto&& callback_pack : on_receive_damage_callbacks[dmg.damage_receiver_id]) {
			if (callback_pack.first == on_receive_damage_policy::after) {
				callback_pack.second(dmg);
			}
		}

		return received_damage;
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
	static void on_receive_damage(size_t entity_id, Callback callback, const on_receive_damage_policy& policy) {
		on_receive_damage_callbacks[entity_id].push_back(std::make_pair(policy, callback));
	}
};

#endif