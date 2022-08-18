#include <power_bullet.h>
#include <turn_based/board.h>
#include <turn_based/components/applied_effects.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/game_controller.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>

power_bullet::power_bullet(entity_id_t entity_id)
    : straight_target_ability(name),
      entity_id_(entity_id),
      full_damage_(get_param_or_default("full_damage", full_damage_)),
      damage_with_power_bullet_effect_(
          get_param_or_default("damage_with_power_bullet_effect", damage_with_power_bullet_effect_)),
      duration_of_effect_(get_param_or_default("duration_of_effect", duration_of_effect_)) {

  configure_hint(config_directory + name + ".json", "hint", full_damage_, duration_of_effect_,
                 damage_with_power_bullet_effect_);

  LOG(debug) << "Power bullet setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage_with_power_bullet_effect: " << damage_with_power_bullet_effect_;
  LOG(debug) << "duration_of_effect: " << duration_of_effect_;
}

void power_bullet::use(index_t index_on) {
  if (used) {
    return;
  }

  auto used_from_index = game_control().selected_index;
  auto caster_id = game_board().at(used_from_index);
  auto enemy_id = game_board().at(index_on);

  auto has_power_bullet_effect = has_effect(enemy_id, "power_bullet_effect");

  sender::send(make_action_message(name, used_from_index, index_on));

  damage_dealers::standard_damage_dealer(magic_damage(has_power_bullet_effect ? damage_with_power_bullet_effect_
                                                                              : full_damage_,
                                                      game_board().at(index_on),
                                                      caster_id));

  if (game::get<entity_manager>().alive(enemy_id)) {
    auto power_bullet_effect_connection =
        make_after_n_round_callback_holder(duration_of_effect_, [enemy_id, caster_id]() mutable {
          remove_effect(enemy_id, "power_bullet_effect");
        });

    auto power_bullet_effect = make_not_removable_positive_effect("power_bullet_effect");
    power_bullet_effect->set_turn_connection(std::move(power_bullet_effect_connection));

    add_effect(enemy_id, power_bullet_effect);
  }

  used = true;
}
