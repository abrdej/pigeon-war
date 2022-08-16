#include <turn_based/ai/movers.h>

#include <iostream>

#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include <turn_based/abilities.h>
#include <turn_based/board.h>
#include <turn_based/board_helpers.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/managers/players_manager.h>

namespace ai::nodes {
namespace {

bool go_close_to_impl(ai_knowledge& knowledge, index_t target_index) {
  auto entity_id = active_entity_id(knowledge);
  auto entity_index = game_board().index_for(active_entity_id(knowledge));

  auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
  auto moving = abilities_ptr->of_type(ability_types::moving);
  if (!moving) return false;

  path_finder distance_finder(false);
  distance_finder.calc(entity_index);

  std::vector<index_t> neighbors;
  board_helpers::neighboring_fields(target_index, neighbors, false);

  boost::range::remove_erase_if(neighbors, [entity_index](index_t index) {
    return !game_board().empty(index) && index != entity_index;
  });

  auto closest_index_it = boost::range::min_element(
      neighbors, [&distance_finder](index_t index_a, index_t index_b) {
        return distance_finder.distance_to(index_a) < distance_finder.distance_to(index_b);
      });
  if (closest_index_it == std::end(neighbors)) {
    return false;
  }

  auto closest_index = *closest_index_it;
  if (closest_index == entity_index) return true;

  std::vector<index_t> path;
  distance_finder.path_to(closest_index, path);

  try_prepare_ability(*moving, entity_index);
  for (auto step : path) {
    if (game_control().is_possible_movement(step)) {
      game_control().do_action(step);
      return true;
    }
  }
  return false;
}

}  // namespace

bool go_to::operator()(ai_knowledge& knowledge) {
  LOG(debug) << "try run go_to node";

  auto entity_id = active_entity_id(knowledge);
  auto entity_index = game_board().index_for(active_entity_id(knowledge));

  auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
  auto moving = abilities_ptr->of_type(ability_types::moving);
  if (!moving) return false;

  if (!knowledge.entity(entity_id).has("destination_index")) {
    return false;
  }

  auto destination_index = knowledge.entity(entity_id).get<index_t>("destination_index");
  if (destination_index == entity_index) {
    return true;
  }

  path_finder path_finder(false);
  path_finder.calc(entity_index);

  std::vector<index_t> path;
  path_finder.path_to(destination_index, path);

  try_prepare_ability(*moving, entity_index);

  for (auto step : path) {
    if (game_control().is_possible_movement(step)) {
      game_control().do_action(step);
      return true;
    }
  }
  return false;
}

bool go_close_to_destination::operator()(ai_knowledge& knowledge) {
  LOG(debug) << "try run go_close_to_destination node";

  auto entity_id = active_entity_id(knowledge);

  if (!knowledge.entity(entity_id).has("destination_index")) {
    return false;
  }

  auto destination_index = knowledge.entity(entity_id).get<index_t>("destination_index");

  return go_close_to_impl(knowledge, destination_index);
}

bool go_close_to_target_index::operator()(ai_knowledge& knowledge) {
  LOG(debug) << "try run go_close_to_target_index node";

  auto entity_id = active_entity_id(knowledge);

  if (!knowledge.entity(entity_id).has("target_enemy_index")) {
    return false;
  }

  auto target_enemy_index = knowledge.entity(entity_id).get<index_t>("target_enemy_index");

  return go_close_to_impl(knowledge, target_enemy_index);
}

bool can_go_to::operator()(ai_knowledge& knowledge) {
  LOG(debug) << "try run can_go_to node";

  auto entity_id = active_entity_id(knowledge);
  auto entity_index = game_board().index_for(active_entity_id(knowledge));

  auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
  auto moving = abilities_ptr->of_type(ability_types::moving);
  if (!moving) return false;

  auto destination_index = knowledge.entity(entity_id).get<index_t>("destination_index");
  if (destination_index == entity_index) {
    return true;
  }

  try_prepare_ability(*moving, entity_index);

  return game_control().is_possible_movement(destination_index);
}

run_around::run_around()
    : shifts({{1, 0}, {0, 1}, {0, 1}, {-1, 0}, {-1, 0}, {0, -1}, {0, -1}, {1, 0}}),
      shift_index(0) {}

bool run_around::operator()(ai_knowledge& knowledge) {
  auto player_id = active_player_id(knowledge);
  auto entity_id = active_entity_id(knowledge);
  auto entity_index = game_board().index_for(active_entity_id(knowledge));

  auto abilities_ptr = game::get<entity_manager>().get(entity_id).get<abilities>();
  auto moving = abilities_ptr->of_type(ability_types::moving);
  if (!moving) return false;

  auto pos = game_board().to_pos(entity_index);
  auto shift = shifts[(shift_index++ % shifts.size())];
  pos.first += shift.first;
  pos.second += shift.second;
  auto destination_index = game_board().to_index(pos.first, pos.second);

  try_prepare_ability(*moving, entity_index);

  if (game_control().is_possible_movement(destination_index)) {
    game_control().do_action(destination_index);
    return true;
  } else {
    if (!game_board().empty(destination_index) &&
        game::get<players_manager>().enemy_entity(player_id, game_board().at(destination_index))) {
      knowledge.entity(entity_id).insert("target_enemy_index", destination_index);

      return false;
    }
  }
  return true;
}

}  // namespace ai::nodes
