#include "lightning.h"
#include <components/applied_effects.h>
#include <components/damage_pack.h>
#include <components/power_field.h>
#include <managers/entity_manager.h>
#include "damage_dealers.h"
#include "power_cost_ability.h"

lightning::lightning(std::uint32_t entity_id) : path_target_ability(3), entity_id_(entity_id) {}

std::string lightning::hint() const {
  auto power = game::get<entity_manager>().get(entity_id_).get<power_filed>()->power;

  auto desc = get_desc("lightning");
  str_replace(desc, "<power>", std::to_string(power));
  str_replace(desc, "<damage>", std::to_string(damage_));
  str_replace(desc, "<power_cost>", std::to_string(power_cost_));

  return desc;
}

bool lightning::usable() const {
  auto& power = game::get<entity_manager>().get(entity_id_).get<power_filed>()->power;
  return power >= power_cost_;
}

void lightning::use(std::uint32_t index_on) {
  if (used) return;

  auto& power = game::get<entity_manager>().get(entity_id_).get<power_filed>()->power;
  if (power < power_cost_) {
    return;
  }

  auto used_from_index = game_control().selected_index_;
  auto caster_id = game_board().at(used_from_index);
  auto enemy_id = game_board().at(index_on);
  auto damage = damage_;

  sender::send(make_action_message("lightning_prepare", index_on));

  auto lightning_connection =
      make_after_n_round_callback_holder(1, [enemy_id, caster_id, damage]() mutable {
        if (game::get<entity_manager>().alive(enemy_id)) {
          sender::send(make_action_message("lightning", game_board().index_for(enemy_id)));
          damage_dealers::standard_damage_dealer(magic_damage(
              damage, enemy_id,
              game::get<entity_manager>().alive(caster_id) ? caster_id : no_damage_dealer));
          remove_effect(enemy_id, "lightning target");
        }
      });

  auto lightning_target = make_not_removable_negative_effect("lightning target");
  lightning_target->set_turn_connection(std::move(lightning_connection));

  add_effect(enemy_id, lightning_target);

  power -= power_cost_;
  sender::send(make_action_message("change_power", entity_id_, -power_cost_));

  used = true;
}
