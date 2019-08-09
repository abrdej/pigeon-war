#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

#include <components/damage_pack.h>
#include <components/health_field.h>
#include <components/modification.h>
#include <core/board.h>
#include <core/game.h>
#include <managers/entity_manager.h>

void play_change_health_animation(std::uint32_t to_index, std::uint32_t entity_id, std::int32_t change_health);

void play_power_change_animation(std::uint32_t to_index, std::int32_t change_power);

std::unordered_map<std::uint32_t, std::int32_t> get_healths();

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

    std::int32_t receive_damage(const damage_pack& dmg) {
        auto receiver_entity = game::get<entity_manager>().get(dmg.damage_receiver_id);

        damage_pack damage_pack = dmg;

        if (receiver_entity.contain<modification>()) {
            damage_pack.damage_value += receiver_entity.get<modification>()->value(modifiers::damage_receiver);
        }
        if (dmg.damage_dealer_id != no_damage_dealer) {
            auto dealer_entity = game::get<entity_manager>().get(dmg.damage_dealer_id);
            if (dealer_entity.contain<modification>()) {
                damage_pack.damage_value += dealer_entity.get<modification>()->value(modifiers::damage_dealer);
            }
        }

        for (auto&& callback_pack : on_receive_damage_before_callbacks) {
            callback_pack.second(damage_pack);
        }

        auto health_pack = receiver_entity.get<health_field>();

        auto received_damage = damage_receiver(*health_pack, damage_pack);

        auto enemy_index = game_board().index_for(damage_pack.damage_receiver_id);
        play_change_health_animation(enemy_index, damage_pack.damage_receiver_id, -received_damage);

        for (auto&& callback_pack : on_receive_damage_after_callbacks) {
            callback_pack.second(damage_pack);
        }

        return received_damage;
    }

    std::int32_t heal(const heal_pack& heal_pack) {
        auto receiver_entity = game::get<entity_manager>().get(heal_pack.receiver_id);

        auto health_pack = receiver_entity.get<health_field>();

        auto heal_amount = heal_pack.heal_value;

        if (heal_pack.heal_type == heal_types::to_base_health) {
            heal_amount = std::min(heal_amount, health_pack->base_health - health_pack->health);
        }

        health_pack->health += heal_amount;

        play_change_health_animation(game_board().index_for(heal_pack.receiver_id), heal_pack.receiver_id, heal_amount);

        return heal_amount;
    }

    template <typename Callback>
    std::uint32_t on_receive_damage(Callback callback, const on_receive_damage_policy& policy) {

        static std::uint32_t id_gen = 0;

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

    void remove_on_receive_damage(std::uint32_t callback_id) {
        on_receive_damage_before_callbacks.erase(callback_id);
        on_receive_damage_after_callbacks.erase(callback_id);
    }

private:
    damage_receiver_impl damage_receiver;
    std::unordered_map<std::uint32_t, std::function<void(const damage_pack&)>> on_receive_damage_before_callbacks;
    std::unordered_map<std::uint32_t, std::function<void(const damage_pack&)>> on_receive_damage_after_callbacks;
};

template <typename DamageReceiver>
inline void set_damage_receiver(std::uint32_t entity_id, DamageReceiver damage_receiver) {
    game::get<entity_manager>().get(entity_id).get<damage_taker>()->set_damage_receiver(damage_receiver);
}

template <typename Callback>
inline std::uint32_t on_receive_damage(std::uint32_t entity_id,
                                       Callback callback,
                                       const damage_taker::on_receive_damage_policy& policy) {
    return game::get<entity_manager>().get(entity_id).get<damage_taker>()->on_receive_damage(callback, policy);
}

inline void remove_on_receive_damage(std::uint32_t entity_id, std::uint32_t callback_id) {
    game::get<entity_manager>().get(entity_id).get<damage_taker>()->remove_on_receive_damage(callback_id);
}

inline auto get_damage_receiver(std::uint32_t entity_id) {
    return game::get<entity_manager>().get(entity_id).get<damage_taker>()->get_damage_receiver();
}

inline void set_destructible(std::uint32_t entity_id, bool value) {
    game::get<entity_manager>().get(entity_id).get<health_field>()->is_destructible = value;
}
