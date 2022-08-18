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

class game_controller {
 public:
  void on_board(std::uint32_t col, std::uint32_t row);
  void on_button(std::uint32_t n);
  void defeat();
  void victory(std::uint32_t player_id);
  void wait_for_action(const std::function<void(index_t index)>& caller);
  void do_action(index_t index);
  bool is_possible_movement(index_t index) const;
  bool valid_target(index_t target_index);
  void set_custom_valid_targets(entity_id_t entity_id, const std::vector<entity_id_t>& custom_entities_targets);
  void set_custom_valid_targets(entity_id_t entity_id, const std::vector<index_t>& custom_indices_targets);

  index_t selected_index_{null_index};
  states_types actual_state_{states_types::waiting};
  target_types actual_targeting_type_{target_types::non};
  std::vector<index_t> possible_movements_;
  std::vector<std::uint32_t> possible_movements_costs_;

 private:
  void set_entity_default_state(index_t select_from_index);

  std::function<void(index_t)> action_;
  std::unordered_map<entity_id_t, std::unordered_set<entity_id_t>> custom_entities_targets_;
  std::unordered_map<entity_id_t, std::unordered_set<index_t>> custom_indices_targets_;
};

inline auto& game_control() { return game::get<game_controller>(); }
