#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <turn_based/defs.h>
#include <turn_based/game.h>
#include <turn_based/path_finder.h>
#include <turn_based/states.h>

/**
 * @brief Class responsible to control game flow.
 */
class game_controller {
 public:
  void on_board(std::uint32_t col, std::uint32_t row);
  void on_button(std::uint32_t n);
  void defeat();
  void victory(player_id_t player_id);
  void wait_for_action(const std::function<void(index_t index)>& caller);
  void do_action(index_t index);
  bool is_possible_movement(index_t index) const;
  bool valid_target(index_t target_index);
  void add_custom_valid_target_entities(entity_id_t entity_id, const std::vector<entity_id_t>& custom_target_entities);
  void add_custom_valid_target_indices(entity_id_t entity_id, const std::vector<index_t>& custom_target_indices);
  void reset_custom_valid_targets_entities(entity_id_t entity_id);
  void reset_custom_valid_targets_indices(entity_id_t entity_id);

  index_t selected_index{null_index};
  states_types current_state{states_types::waiting};
  target_types current_targeting_type{target_types::non};
  std::vector<index_t> possible_movements;
  std::vector<std::uint32_t> possible_movements_costs;

 private:
  void set_entity_default_state(index_t select_from_index);

  std::function<void(index_t)> action_;
  std::unordered_map<entity_id_t, std::unordered_set<entity_id_t>> custom_target_entities_;
  std::unordered_map<entity_id_t, std::unordered_set<index_t>> custom_target_indices_;
};

inline auto& game_control() { return game::get<game_controller>(); }
