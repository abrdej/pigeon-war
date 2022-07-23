#include <sword_blow.h>

#include <turn_based/board.h>
#include <turn_based/components/health_field.h>
#include <turn_based/damage_dealers.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/messages/massages_makers.h>
#include <turn_based/sender.h>

sword_blow::sword_blow(std::uint32_t entity_id)
    : neighboring_target_ability(name),
      entity_id_(entity_id),
      damage_(get_param_or_default("damage", damage_)) {

  configure_hint(config_directory + name + ".json", "hint", damage_);

  LOG(debug) << "Sword blow setup:";
  LOG(debug) << "entity_id: " << entity_id_;
  LOG(debug) << "damage: " << damage_;
}

void sword_blow::use(std::uint32_t index_on) {
  if (used) return;

  auto used_from_index = game_control().selected_index_;

  std::vector<std::uint32_t> around_fields_ids;
  board_helper::neighboring_fields(used_from_index, around_fields_ids, false);

  sender::send(make_action_message(name, used_from_index));

  std::int32_t hit_entities_counter = 0;

  // make local copy as we can die while do sword blow
  auto damage = damage_;
  auto entity_id = entity_id_;

  for (auto field_id : around_fields_ids) {
    if (!game_board().empty(field_id) && game_get<entity_manager>()
                                             .get(game_board().at(field_id))
                                             .get<health_field>()
                                             ->is_destructible) {
      auto final_damage = damage_dealers::standard_damage_dealer(
          melee_damage(damage, game_board().at(field_id), entity_id));
      // if (final_damage != 0) {
      ++hit_entities_counter;
      //}
    }
  }

  if (hit_entities_counter >= 3 && game_get<entity_manager>().alive(entity_id)) {
    sender::send(make_action_message(name, used_from_index));
    for (auto field_id : around_fields_ids) {
      if (!game_board().empty(field_id)) {
        damage_dealers::standard_damage_dealer(
            melee_damage(damage, game_board().at(field_id), entity_id));
      }
    }
  }

  used = true;
}
