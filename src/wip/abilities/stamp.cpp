#include <stamp.h>

#include <turn_based/abilities.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/move.h>
#include <components/applied_effects.h>
#include <components/damage_taker.h>
#include <components/power_field.h>

stamp::stamp(std::uint32_t entity_id) : entity_id_(entity_id) {}

void stamp::use(std::uint32_t on_index) {
  if (used) return;

  sender::send(make_action_message("stamp", entity_id_, on_index));
  damage_dealers::standard_damage_dealer(
      melee_damage(damage_, game_board().at(on_index), entity_id_));

  auto enemy_id = game_board().at(on_index);
  if (game::get<entity_manager>().alive(enemy_id)) {
    if (has_effect(enemy_id, "sparks_effect")) {
      remove_effect(enemy_id, "sparks_effect");
    }

    auto connection = on_receive_damage(
        enemy_id,
        [entity_id = entity_id_, healing_amount = healing_amount_](const damage_pack& dmg) {
          if (game_get<entity_manager>().alive(entity_id)) {
            auto power = game::get<entity_manager>().get(entity_id).get<power_filed>();

            auto power_increase =
              std::min<std::int32_t>(power->power + healing_amount, power->max_power) - power->power;
            power->power += power_increase;

            sender::send(make_action_message("change_power", entity_id, power_increase));

            // standard_healing(healing_above_base_health(healing_amount, entity_id));
            //            auto damage = std::min(health_pack.health, dmg.damage_value - power_burn);
            //            health_pack.health -= damage;
          }
        },
        on_receive_damage_policy::after);

    auto sparks_connection = make_after_n_round_callback_holder(
        sparks_duration_,
        [enemy_id]() mutable { remove_effect(enemy_id, "sparks_effect"); });

    auto sparks_effect = make_negative_effect("sparks_effect");
    sparks_effect->set_turn_connection(std::move(sparks_connection));
    sparks_effect->set_on_destruction([connection]() { connection.disconnect(); });
    add_effect(enemy_id, sparks_effect);

    if (++stamps_ == stamps_to_stun_) {
      stamps_ = 0;

      game::get<entity_manager>().get(enemy_id).get<abilities>()->is_active = false;

      // auto enemy_abilities = game_get<entity_manager>().get(enemy_id).get<abilities>();
      // auto moveable =
      //  std::dynamic_pointer_cast<moveable_base>(enemy_abilities->of_type(ability_types::moving));
      // if (moveable) {

      // moveable->set_slow_down(0);
      auto stun_connection =
          make_after_n_round_callback_holder(stun_duration_, [enemy_id]() mutable {
            // moveable->remove_slow_down();

            if (game_get<entity_manager>().alive(enemy_id)) {
              game::get<entity_manager>().get(enemy_id).get<abilities>()->is_active = true;
              remove_effect(enemy_id, "stun");
            }
          });

      auto stun_effect = make_negative_effect("stun_effect");
      stun_effect->set_turn_connection(std::move(stun_connection));
      add_effect(enemy_id, stun_effect);
      //}
    }
  }

  used = true;
}
