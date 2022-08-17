#pragma once

#include <cstdint>
#include <functional>
#include <unordered_map>

#include <boost/signals2.hpp>

#include <turn_based/components/damage_pack.h>
#include <turn_based/components/health_field.h>
#include <turn_based/components/modification.h>
#include <turn_based/board.h>
#include <turn_based/game.h>
#include <turn_based/managers/entity_manager.h>

using damage_scoped_connection = boost::signals2::scoped_connection;
using damage_connection = boost::signals2::connection;
using damage_signal = boost::signals2::signal<void(const damage_pack&)>;
using damage_slot = damage_signal::slot_type;
using damage_turn_slot = damage_signal::extended_slot_type;

void send_change_health_message(index_t to_index, entity_id_t entity_id, std::int32_t change_health);

void send_change_power_message(index_t to_index, std::int32_t change_power);

std::unordered_map<entity_id_t, std::int32_t> get_healths();

enum class on_receive_damage_policy { before, after };

using damage_fn = std::function<std::int32_t(health_field&, const damage_pack&)>;

/**
 * @brief This class is responsible for handling damage and healing.
 */
class damage_manager {
  class damage_receiver_impl {
   public:
    damage_receiver_impl() {
      impl_ = [](health_field& health_pack, const damage_pack& dmg) {
        auto final_damage = (std::min)(health_pack.health, dmg.damage_value);
        health_pack.health -= final_damage;
        return final_damage;
      };
    }

    template <typename Callback>
    explicit damage_receiver_impl(Callback callback) : impl_(callback) {}

    template <typename Callback>
    damage_receiver_impl& operator=(Callback callback) {
      impl_ = callback;
      return *this;
    }

    [[nodiscard]] explicit operator damage_fn() const { return impl_; }

    std::int32_t operator()(health_field& entity_id, const damage_pack& dmg) const {
      return impl_(entity_id, dmg);
    }

   private:
    damage_fn impl_;
  };

  std::unordered_map<entity_id_t, damage_receiver_impl> damage_receivers_;
  damage_signal receive_damage_before_signal_;
  damage_signal receive_damage_after_signal_;

 public:
  std::int32_t deal_damage(const damage_pack& dmg) {
    auto receiver_entity = game::get<entity_manager>().get(dmg.damage_receiver_id);

    damage_pack damage_pack = dmg;

    if (receiver_entity.contain<modification>()) {
      damage_pack.damage_value +=
        receiver_entity.get<modification>()->value(modifiers::damage_receiver);
    }
    if (dmg.damage_dealer_id != no_damage_dealer) {
      auto dealer_entity = game::get<entity_manager>().get(dmg.damage_dealer_id);
      if (dealer_entity.contain<modification>()) {
        damage_pack.damage_value +=
          dealer_entity.get<modification>()->value(modifiers::damage_dealer);
      }
    }

    receive_damage_before_signal_(damage_pack);

    auto health_pack = receiver_entity.get<health_field>();

    auto received_damage = damage_receivers_[dmg.damage_receiver_id](*health_pack, damage_pack);

    auto enemy_index = game_board().index_for(damage_pack.damage_receiver_id);
    send_change_health_message(enemy_index, damage_pack.damage_receiver_id, -received_damage);

    receive_damage_after_signal_(damage_pack);

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

    send_change_health_message(game_board().index_for(heal_pack.receiver_id), heal_pack.receiver_id, heal_amount);

    return heal_amount;
  }

  template <typename Callback>
  damage_connection on_receive_damage(Callback callback, const on_receive_damage_policy& policy) {
    return (policy == on_receive_damage_policy::before)
           ? receive_damage_before_signal_.connect(callback) : receive_damage_after_signal_.connect(callback);
  }

  template <typename DamageReceiver>
  void set_damage_receiver(entity_id_t entity_id, DamageReceiver dmg_receiver) {
    damage_receivers_[entity_id] = dmg_receiver;
  }

  damage_fn get_damage_receiver(entity_id_t entity_id) {
    return damage_receivers_[entity_id];
  }
};

template <typename DamageReceiver>
void set_damage_receiver(entity_id_t entity_id, DamageReceiver damage_receiver) {
  game::get<damage_manager>().set_damage_receiver(entity_id, damage_receiver);
}

template <typename Callback>
damage_connection on_receive_damage(entity_id_t entity_id, Callback callback,
                                    const on_receive_damage_policy& policy) {
  return game::get<damage_manager>().on_receive_damage([entity_id, callback](const damage_pack& dmg) mutable {
    if (dmg.damage_receiver_id == entity_id) {
      callback(dmg);
    }
  }, policy);
}

damage_fn get_damage_receiver(entity_id_t entity_id);

void set_destructible(entity_id_t entity_id, bool value);
