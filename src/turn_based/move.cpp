#include <turn_based/move.h>

#include <config.h>
#include <logging/logger.h>
#include <turn_based/board.h>
#include <turn_based/board_helpers.h>
#include <turn_based/game_controller.h>
#include <turn_based/managers/entity_manager.h>

move::move(std::int32_t range, types type)
    : move_ability(name), range_(range), base_range_(range), movement_type_(type) {
  on_every_two_turns_from_next([this]() { used_ = false; });

  configure_hint(config_directory + name + ".json", "hint", range_);

  LOG(debug) << "Move setup:";
  LOG(debug) << "range: " << range;
}

void move::prepare(index_t for_index) {
  game_control().selected_index_ = for_index;
  game_control().actual_state_ = states_types::wait_for_action;

  LOG(debug) << "range: " << range_;

  if (movement_type_ == types::path) {
    path_finder path_finder(skip_collisions_);
    path_finder.calc(for_index);
    path_finder.get_possible_movements(game_control().possible_movements_,
                                       game_control().possible_movements_costs_,
                                       used_ ? 0 : range_);

  } else if (movement_type_ == types::straight) {
    board_helpers::calc_straight(game_control().selected_index_,
                                 game_control().possible_movements_,
                                 game_control().possible_movements_costs_,
                                used_ ? 0 : range_);
  }

  game_control().actual_targeting_type_ = target_types::moving;
  game_control().wait_for_action([this](index_t index) { return do_move(index); });
}

void move::do_move(index_t index_to) {
  if (used_) {
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

  game_control().selected_index_ = null_index;

  sender::send(make_action_message("move", entity_id, index_to));

  game_board().give_back(entity_id, index_to);

  game_control().selected_index_ = index_to;
  game_control().possible_movements_.clear();

  used_ = true;
}
