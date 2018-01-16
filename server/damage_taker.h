//
// Created by abrdej on 16.01.18.
//

#ifndef PIGEONWAR_DAMAGE_TAKER_H
#define PIGEONWAR_DAMAGE_TAKER_H


#include <cstdint>
#include <unordered_map>
#include <functional>
#include <managers/modifications_manager.h>
#include <core/board.h>
#include <managers/health_manager.h>
//#include <managers/entity_manager.h>
#include "damage_pack.h"
#include "common/health_field.h"

class damage_taker {
public:
	enum class on_receive_damage_policy {
		before,
		after
	};
	struct damage_receiver_impl {
		damage_receiver_impl() {
			impl = [](health_field& health_pack, const damage_pack& dmg) {

				auto final_damage = (std::min)(health_pack.health, dmg.damage_value);

				health_pack.health -= final_damage;

				return final_damage;
			};
		}
		template <typename Callback>
		explicit damage_receiver_impl(Callback callback) : impl(callback) {
		}
		template <typename Callback>
		damage_receiver_impl& operator=(Callback callback) {
			impl = callback;
			return *this;
		}
		operator std::function<std::int32_t(health_field&, const damage_pack&)>() {
			return impl;
		}
		std::int32_t operator()(health_field& entity_id, const damage_pack& dmg) {
			return impl(entity_id, dmg);
		}
		std::function<std::int32_t(health_field&, const damage_pack&)> impl;
	};

	template <typename DamageReceiver>
	void set_damage_receiver(DamageReceiver dmg_receiver) {
		damage_receiver = dmg_receiver;
	}
	std::function<std::int32_t(health_field&, const damage_pack&)> get_damage_receiver() {
		return damage_receiver;
	}
	const std::function<std::int32_t(health_field&, const damage_pack&)> get_damage_receiver() const {
		return damage_receiver;
	}

	std::int32_t receive_damage(const damage_pack& dmg)
	{
		damage_pack damage_pack = dmg;
		damage_pack.damage_value += modifications_manager::damage_receiver_modifier_value(dmg.damage_receiver_id);

		for (auto&& callback_pack : on_receive_damage_before_callbacks) {
			callback_pack.second(damage_pack);
		}

//		auto health_pack = entity_manager::get(damage_pack.damage_receiver_id).get<health_field>();
//
//		auto received_damage = damage_receiver(*health_pack, damage_pack);
//
//		auto enemy_index = board::index_for(damage_pack.damage_receiver_id);
//		play_change_health_animation(enemy_index, -received_damage);
//
//		for (auto&& callback_pack : on_receive_damage_after_callbacks) {
//			callback_pack.second(damage_pack);
//		}

		int received_damage{};

		return received_damage;
	}

	template <typename Callback>
	std::uint64_t on_receive_damage(Callback callback, const on_receive_damage_policy& policy) {

		static std::uint64_t id_gen = 0;

		if (policy == on_receive_damage_policy::before) {
			auto callback_id = id_gen++;
			on_receive_damage_before_callbacks.emplace(callback_id, callback);
			return callback_id;

		} else {
			auto callback_id = id_gen++;
			on_receive_damage_after_callbacks.emplace(callback_id, callback);
			return callback_id;
		}
	}

	void remove_on_receive_damage(std::uint64_t callback_id) {
		on_receive_damage_before_callbacks.erase(callback_id);
		on_receive_damage_after_callbacks.erase(callback_id);
	}

private:
	damage_receiver_impl damage_receiver;
	std::unordered_map<std::uint64_t, std::function<void(const damage_pack&)>> on_receive_damage_before_callbacks;
	std::unordered_map<std::uint64_t, std::function<void(const damage_pack&)>> on_receive_damage_after_callbacks;
};


#endif //PIGEONWAR_DAMAGE_TAKER_H
