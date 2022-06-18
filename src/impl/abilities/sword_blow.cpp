#include <sword_blow.h>

#include <turn_based/damage_dealers.h>
#include <turn_based/board.h>

sword_blow::sword_blow(std::uint32_t entity_id) : entity_id_(entity_id) {}

void sword_blow::use(std::uint32_t index_on) {
  if (used) return;

  auto used_from_index = game_control().selected_index_;

  std::vector<std::uint32_t> around_fields_ids;
  board_helper::neighboring_fields(used_from_index, around_fields_ids, false);

  sender::send(make_action_message("sword_blow", used_from_index));

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
    sender::send(make_action_message("sword_blow", used_from_index));
    for (auto field_id : around_fields_ids) {
      if (!game_board().empty(field_id)) {
        damage_dealers::standard_damage_dealer(
            melee_damage(damage, game_board().at(field_id), entity_id));
      }
    }
  }

  used = true;
}
