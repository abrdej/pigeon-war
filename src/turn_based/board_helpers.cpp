#include <turn_based/board_helpers.h>

#include <turn_based/board.h>

namespace board_helpers {
namespace detail {

template <long unsigned int N>
using DirectionArray = std::array<std::pair<std::int32_t, std::int32_t>, N>;

template <long unsigned int N>
void calc_helper(const DirectionArray<N>& directions,
                 index_t from_index,
                 std::vector<index_t>& movements,
                 std::vector<std::uint32_t>& costs,
                 std::int32_t range,
                 bool skip_obstacles) {
  movements.clear();
  costs.clear();

  const auto pos = game_board().to_pos(from_index);
  for (const auto& direction : directions) {
    for (std::int32_t step = 1; step <= range; ++step) {
      auto next_pos = std::make_pair(pos.first + direction.first * step, pos.second + direction.second * step);

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
  const detail::DirectionArray<4> directions = {
      std::make_pair(-1, 0), std::make_pair(+1, 0),
      std::make_pair(0, +1), std::make_pair(0, -1)};

  detail::calc_helper(directions, from_index, movements, costs, range, skip_obstacles);
}

void calc_diagonal(index_t from_index, std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range, bool skip_obstacles) {
  const detail::DirectionArray<4> directions = {
      std::make_pair(-1, -1), std::make_pair(+1, +1),
      std::make_pair(-1, +1), std::make_pair(+1, -1)};

  detail::calc_helper(directions, from_index, movements, costs, range, skip_obstacles);
}

void calc_directed(index_t from_index, std::vector<index_t>& movements,
                   std::vector<std::uint32_t>& costs, std::int32_t range, bool skip_obstacles) {
  const detail::DirectionArray<8> directions = {
      std::make_pair(-1, 0),  std::make_pair(+1, 0),
      std::make_pair(0, +1), std::make_pair(0, -1),
      std::make_pair(-1, -1), std::make_pair(+1, +1),
      std::make_pair(-1, +1), std::make_pair(+1, -1)};

  detail::calc_helper(directions, from_index, movements, costs, range, skip_obstacles);
}

void neighboring_fields(index_t for_index, std::vector<index_t>& fields, bool available) {
  fields.clear();
  auto pos = game_board().to_pos(for_index);

  for (std::int32_t x = -1; x <= 1; ++x) {
    for (std::int32_t y = -1; y <= 1; ++y) {
      auto pos_x = pos.first + x;
      auto pos_y = pos.second + y;
      auto index = game_board().to_index(pos_x, pos_y);
      if ((x || y) && pos_x < game_board().cols_n && pos_y < game_board().rows_n &&
          (!available || game_board().empty(index))) {
        fields.push_back(game_board().to_index(pos_x, pos_y));
      }
    }
  }
}

void circle(index_t for_index, std::vector<index_t>& fields, bool available) {
  fields.clear();
  auto pos = game_board().to_pos(for_index);

  for (std::int32_t x = -2; x <= 2; ++x) {
    for (std::int32_t y = -2; y <= 2; ++y) {
      if (abs(x) == 2 || abs(y) == 2) {
        auto pos_x = pos.first + x;
        auto pos_y = pos.second + y;
        auto index = game_board().to_index(pos.first + x, pos_y);
        if ((x || y) && pos_x < game_board().cols_n && pos_y < game_board().rows_n &&
            (!available || game_board().empty(index))) {
          fields.push_back(game_board().to_index(pos_x, pos_y));
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
