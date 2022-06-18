#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <vector>

#include <boost/signals2.hpp>

#include <turn_based/game.h>

// TODO: refactor with board container
struct board {
  static const std::uint32_t empty_id = std::numeric_limits<std::uint32_t>::max();

  using board_change_signal = boost::signals2::signal<void()>;
  board_change_signal board_change_signal_;

  template <typename SlotType>
  void on_change(SlotType x) {
    board_change_signal_.connect(x);
  }

  void insert(std::uint32_t on_index, std::uint32_t entity_id);
  void remove(std::uint32_t from_index);
  std::uint32_t move(std::uint32_t from_index, std::uint32_t to_index);
  std::uint32_t take(std::uint32_t from_index);
  std::uint32_t take_bottom(std::uint32_t from_index);
  void give_back(std::uint32_t entity_id, std::uint32_t to_index);
  std::uint32_t at(std::uint32_t at_index);
  bool empty(std::uint32_t at_index);
  std::uint32_t index_for(std::uint32_t entity_id);
  void remove_entity(std::uint32_t entity_id);
  void for_each(const std::function<void(std::uint32_t entity_id, std::uint32_t col, std::uint32_t row)>& func);
  void set_size(std::uint32_t cols, std::uint32_t rows);
  std::pair<std::uint32_t, std::uint32_t> to_pos(std::uint32_t index);
  std::uint32_t to_index(std::uint32_t col, std::uint32_t row);
  bool is_valid(std::uint32_t col, std::uint32_t row);

  std::uint32_t cols_n{0};
  std::uint32_t rows_n{0};
  std::vector<std::vector<std::uint32_t>> fields_;
};

inline auto& game_board() { return game::get<board>(); }

namespace std {

template <typename CharT>
basic_ostream<CharT>& operator<<(basic_ostream<CharT>& os, const pair<uint32_t, uint32_t>& pos) {
  os << "(" << pos.first << ", " << pos.second << ")";
  return os;
}

}  // namespace std
