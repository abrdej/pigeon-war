#include <turn_based/board_helpers.h>

#include <turn_based/board.h>

namespace board_helper {
namespace detail {

template <long unsigned int N>
void calc_helper(const std::array<std::pair<std::int32_t, std::int32_t>, N>& ops,
                 index_t from_index,
                 std::vector<index_t>& movements,
                 std::vector<std::uint32_t>& costs,
                 std::int32_t range,
                 bool skip_obstacles) {
  movements.clear();
  costs.clear();

  const auto pos = game_board().to_pos(from_index);
  for (const auto& op : ops) {
    for (std::int32_t step = 1; step <= range; ++step) {
      auto next_pos = std::make_pair(pos.first + op.first * step, pos.second + op.second * step);

      if (next_pos.first < 0 || next_pos.second < 0 || next_pos.first >= game_board().cols_n
          || next_pos.second >= game_board().rows_n) {
        break;
      }

      const auto index = game_board().to_index(next_pos.first, next_pos.second);

      costs.push_back(step);
      movements.push_back(index);

      if (!game_board().empty(index) && !skip_obstacles) {
        break;
      }
    }
  }
}

}  // namespace detail

void calc_straight(index_t from_index, std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range, bool skip_obstacles) {
  const std::array<std::pair<std::int32_t, std::int32_t>, 4> ops = {
      std::make_pair(-1, 0), std::make_pair(+1, 0), std::make_pair(0, +1), std::make_pair(0, -1)};

  detail::calc_helper(ops, from_index, movements, costs, range, skip_obstacles);
}

void calc_diagonal(index_t from_index, std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range, bool skip_obstacles) {
  const std::array<std::pair<std::int32_t, std::int32_t>, 4> ops = {
      std::make_pair(-1, -1), std::make_pair(+1, +1), std::make_pair(-1, +1),
      std::make_pair(+1, -1)};

  detail::calc_helper(ops, from_index, movements, costs, range, skip_obstacles);
}

void calc_directed(index_t from_index, std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range, bool skip_obstacles) {
  const std::array<std::pair<std::int32_t, std::int32_t>, 8> ops = {
      std::make_pair(-1, 0),  std::make_pair(+1, 0),  std::make_pair(0, +1),
      std::make_pair(0, -1),  std::make_pair(-1, -1), std::make_pair(+1, +1),
      std::make_pair(-1, +1), std::make_pair(+1, -1)};

  detail::calc_helper(ops, from_index, movements, costs, range, skip_obstacles);
}

void neighboring_fields(index_t for_index, std::vector<index_t>& fields, bool available) {
  fields.clear();
  auto fld = game_board().to_pos(for_index);

  for (std::int32_t col = -1; col <= 1; ++col) {
    for (std::int32_t row = -1; row <= 1; ++row) {
      auto col_index = fld.first + col;
      auto row_index = fld.second + row;
      auto index = game_board().to_index(col_index, row_index);
      if ((col || row) && col_index < game_board().cols_n && row_index < game_board().rows_n &&
          (!available || game_board().empty(index))) {
        fields.push_back(game_board().to_index(col_index, row_index));
      }
    }
  }
}

void circle(index_t for_index, std::vector<index_t>& fields, bool available) {
  fields.clear();
  auto fld = game_board().to_pos(for_index);

  for (std::int32_t col = -2; col <= 2; ++col) {
    for (std::int32_t row = -2; row <= 2; ++row) {
      if (abs(col) == 2 || abs(row) == 2) {
        auto col_index = fld.first + col;
        auto row_index = fld.second + row;
        auto index = game_board().to_index(col_index, row_index);
        if ((col || row) && col_index < game_board().cols_n && row_index < game_board().rows_n &&
            (!available || game_board().empty(index))) {
          fields.push_back(game_board().to_index(col_index, row_index));
        }
      }
    }
  }
}

void all_free(std::vector<index_t>& fields) {
  for (std::uint32_t index = 0; index < game_board().rows_n * game_board().cols_n; ++index) {
    if (game_board().empty(index_t{index})) {
      fields.emplace_back(index_t{index});
    }
  }
}

void all(std::vector<index_t>& fields) {
  for (std::uint32_t index = 0; index < game_board().rows_n * game_board().cols_n; ++index) {
    fields.emplace_back(index_t{index});
  }
}

}  // namespace board_helper
