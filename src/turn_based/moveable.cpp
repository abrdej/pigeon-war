#include <turn_based/moveable.h>

#include <turn_based/board.h>
#include <logging/logger.h>
#include <turn_based/managers/entity_manager.h>
#include <turn_based/game_controller.h>

void moveable::prepare(std::uint32_t for_index) {
  game_control().selected_index_ = for_index;
  game_control().actual_state_ = states_types::wait_for_action;

  LOG(debug) << "range: " << range;

  if (movement_type == types::path) {
    path_finder path_finder(skip_collisions_);
    path_finder.calc(for_index);
    path_finder.get_possible_movements(game_control().possible_movements_,
                                       game_control().possible_movements_costs_,
                                       used ? 0 : range);

  } else if (movement_type == types::straight) {
    board_helper::calc_straight(game_control().selected_index_,
                                game_control().possible_movements_,
                                game_control().possible_movements_costs_,
                                used ? 0 : range);
  }

  game_control().actual_targeting_type_ = target_types::moving;
  game_control().wait_for_action([this](std::uint32_t index) { return move(index); });
}

void moveable::move(std::uint32_t index_to) {
  if (used) {
    return;
  }

  std::uint32_t i = 0;
  for (; i < game_control().possible_movements_.size(); ++i) {
    if (game_control().possible_movements_[i] == index_to) break;
  }
  auto cost = static_cast<std::int32_t>(game_control().possible_movements_costs_[i]);

  auto move_from_index = game_control().selected_index_;

  auto entity_id = game_board().take(move_from_index);

  call_move_callbacks(move_from_index, index_to, cost);

  game_control().selected_index_ = no_selected_index;

  //	sender::send(make_action_message("move", move_from_index, index_to));
  sender::send(make_action_message("move", entity_id, index_to));

  std::int32_t from_col = game_board().to_pos(move_from_index).first;
  std::int32_t to_col = game_board().to_pos(index_to).first;

  game_board().give_back(entity_id, index_to);

  game_control().selected_index_ = index_to;
  game_control().possible_movements_.clear();

  used = true;
}