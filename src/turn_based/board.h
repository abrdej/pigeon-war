#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <vector>

#include <boost/signals2.hpp>

#include <turn_based/defs.h>
#include <turn_based/game.h>

// TODO: refactor with board container
struct board {
  using board_change_signal = boost::signals2::signal<void()>;
  board_change_signal board_change_signal_;

  template <typename SlotType>
  void on_change(SlotType x) {
    board_change_signal_.connect(x);
  }

  void insert(index_t on_index, entity_id_t entity_id);
  void remove(index_t from_index);
  entity_id_t move(index_t from_index, index_t to_index);
  entity_id_t take(index_t from_index);
  entity_id_t take_bottom(index_t from_index);
  void give_back(entity_id_t entity_id, index_t to_index);
  entity_id_t at(index_t at_index);
  bool empty(index_t at_index);
  index_t index_for(entity_id_t entity_id);
  void remove_entity(entity_id_t entity_id);
  void for_each(const std::function<void(entity_id_t entity_id, std::uint32_t col, std::uint32_t row)>& func);
  void set_size(std::uint32_t cols, std::uint32_t rows);
  std::pair<std::uint32_t, std::uint32_t> to_pos(index_t index);
  index_t to_index(std::uint32_t col, std::uint32_t row);
  bool is_valid(std::uint32_t col, std::uint32_t row);

  std::uint32_t cols_n{0};
  std::uint32_t rows_n{0};
  std::vector<std::vector<entity_id_t>> fields_;
};

inline auto& game_board() { return game::get<board>(); }

namespace std {

template <typename CharT>
basic_ostream<CharT>& operator<<(basic_ostream<CharT>& os, const pair<uint32_t, uint32_t>& pos) {
  os << "(" << pos.first << ", " << pos.second << ")";
  return os;
}

}  // namespace std
