#include <magic_bullet.h>

#include <logging/logger.h>
#include <turn_based/board_helpers.h>
#include <turn_based/components/damage_taker.h>
#include <turn_based/components/power_field.h>
#include <turn_based/damage_dealers.h>

magic_bullet::magic_bullet(entity_id_t entity_id)
    : path_target_ability(name, 3),
      entity_id_(entity_id),
      magic_power_accumulation_amount_(
          get_param_or_default("magic_power_accumulation_amount", magic_power_accumulation_amount_)),
      magic_power_drain_amount_(get_param_or_default("magic_power_drain_amount", magic_power_drain_amount_)) {

  auto power = game::get<entity_manager>().get(entity_id_).get<power_filed>();

  after_player_turn(entity_id_, [this, entity_id, power]() {
    if (first_used_) {
      used_ = false;
      std::int32_t power_backup = power->power;

      power->power += magic_power_accumulation_amount_;

      std::vector<index_t> neighbors;
      board_helpers::neighboring_fields(game_board().index_for(entity_id), neighbors, false);
      for (auto index : neighbors) {
        if (!game_board().empty(index) && players_helpers::is_enemy_entity_at(index)) {
          power->power += magic_power_drain_amount_;
          sender::send(make_action_message("magic_suck", index));
        }
      }
      sender::send(make_action_message("change_power", entity_id, power->power - power_backup));
    }
  });

  set_damage_receiver(entity_id_, [entity_id, power](health_field& health_pack, const damage_pack& dmg) mutable {
    auto half_damage = static_cast<std::int32_t>(dmg.damage_value * 0.5f);

    auto power_burn = std::min<std::int32_t>(power->power, half_damage);
    power->power -= power_burn;
    sender::send(make_action_message("change_power", entity_id, -power_burn));

    auto damage = std::min(health_pack.health, 2 * half_damage - power_burn);
    health_pack.health -= damage;

    return damage;
  });

  configure_hint(config_directory + name + ".json", "hint", magic_power_accumulation_amount_,
                 magic_power_drain_amount_, power->power);

  LOG(debug) << "Magic bullet setup:";
  LOG(debug) << "magic_power_accumulation_amount: " << magic_power_accumulation_amount_;
  LOG(debug) << "magic_power_drain_amount: " << magic_power_drain_amount_;
}

void magic_bullet::use(index_t index_on) {
  if (used_) {
    return;
  }

  auto from_index = game_control().selected_index;

  auto power = game::get<entity_manager>().get(entity_id_).get<power_filed>();

  sender::send(make_action_message(name, entity_id_, index_on));

  damage_dealers::standard_damage_dealer(magic_damage(power->power,
                                                      game_board().at(index_on),
                                                      game_board().at(from_index)));

  auto change_power = -power->power;
  power->power = 0;

  sender::send(make_action_message("change_power", entity_id_, change_power));

  first_used_ = true;
  used_ = true;
}
