#include <magic_bullet.h>

#include <turn_based/damage_dealers.h>
#include <components/damage_taker.h>
#include <components/power_field.h>

magic_bullet::magic_bullet(std::uint32_t entity_id)
    : path_target_ability(3), entity_id(entity_id) {

  auto power = game::get<entity_manager>().get(entity_id).get<power_filed>();

  after_player_turn(entity_id, [this, entity_id, power]() {
    if (first_used) {
      used = false;
      std::int32_t power_backup = power->power;

      power->power += magic_power_accumulation_amount;

      std::vector<std::uint32_t> neighbors;
      board_helper::neighboring_fields(game_board().index_for(entity_id), neighbors, false);
      for (auto index : neighbors) {
        if (!game_board().empty(index) && players_helpers::is_enemy_entity(index)) {
          power->power += magic_power_drain_amount;
          sender::send(make_action_message("magic_suck", index));
        }
      }
      sender::send(make_action_message("change_power", entity_id, power->power - power_backup));
    }
  });

  set_damage_receiver(entity_id, [this, entity_id, power](health_field& health_pack, const damage_pack& dmg) mutable {

    auto half_damage = static_cast<std::int32_t>(dmg.damage_value * 0.5f);

    auto power_burn = std::min<std::int32_t>(power->power, half_damage);
    power->power -= power_burn;
    sender::send(make_action_message("change_power", entity_id, -power_burn));

    auto damage = std::min(health_pack.health, 2 * half_damage - power_burn);
    health_pack.health -= damage;

    return damage;
  });
}

std::string magic_bullet::hint() const {

  auto power = game::get<entity_manager>().get(entity_id).get<power_filed>();

  std::string desc;
  desc = "Magic Bullet - monk accumulates " + std::to_string(magic_power_accumulation_amount) +
         " magic points for each turn.\n"
             "In addition, he accumulates " + std::to_string(magic_power_drain_amount) +
         " magic points for each enemy in his neighborhood.\n"
             "Magic point can be used to deal damage equal to the amount of magic points.\n"
             "Additionally, half of the damage that monk receive firstly must destroys\n"
             " the magic shiled which is formed from this points.\n"
             "Magic power: " + std::to_string(power->power) + ".";

  return std::move(desc);
}

void magic_bullet::use(std::uint32_t index_on) {
  if (used)
    return;

  auto from_index = game_control().selected_index_;

  auto power = game::get<entity_manager>().get(entity_id).get<power_filed>();

  sender::send(make_action_message("magic_bullet", entity_id, index_on));

  damage_dealers::standard_damage_dealer(
      magic_damage(power->power, game_board().at(index_on), game_board().at(from_index)));

  auto change_power = -power->power;
  power->power = 0;

  sender::send(make_action_message("change_power", entity_id, change_power));

  first_used = true;
  used = true;
}
