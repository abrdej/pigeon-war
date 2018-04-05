#include "path_finder.h"
#include "board.h"
#include "abilities/moveable.h"

path_finder::path_finder(bool all_fields)
		: start_index_(-1)
{
	board_graph.set_size(board::cols_n * board::rows_n);

	board::for_each([this, &all_fields](std::uint32_t entity_id, std::uint32_t col, std::uint32_t row) {
		auto rows_n = board::rows_n;
		auto cols_n = board::cols_n;
		auto key_from = board::to_index(col, row);

		if (row < rows_n - 1) {
			auto key_to = board::to_index(col, row + 1);
			if (board::empty(key_to) || all_fields)
				board_graph.add_edge(key_from, key_to);

			if (board::empty(key_from) || all_fields)
				board_graph.add_edge(key_to, key_from);
		}
		if (col < cols_n - 1) {
			auto key_to = board::to_index(col + 1, row);
			if (board::empty(key_to) || all_fields)
				board_graph.add_edge(key_from, key_to);

			if (board::empty(key_from) || all_fields)
				board_graph.add_edge(key_to, key_from);
		}
	});
}

void path_finder::calc(std::uint32_t from_index)
{
	start_index_ = from_index;
	distance_map_.clear();
	sequence_map_.clear();
	breadth_search(board_graph, from_index, distance_map_, sequence_map_);
}

std::uint32_t path_finder::find_first_satisfy_conditions(std::uint32_t from_index, const std::function<bool(std::uint32_t)>& condition_fn)
{
	start_index_ = from_index;
	distance_map_.clear();
	sequence_map_.clear();
	return breadth_search(board_graph, from_index, distance_map_, sequence_map_, condition_fn);
}

void path_finder::get_possible_movements(std::vector<std::uint32_t>& movements,
										 std::vector<std::uint32_t>& costs,
										 std::int32_t range)
{
	movements.clear();
	costs.clear();
	for (std::size_t i = 0; i < distance_map_.size(); ++i)
		if (distance_map_[i] <= range && distance_map_[i] != 0)
		{
			movements.emplace_back(i);
			costs.emplace_back(distance_map_[i]);
		}
}

void path_finder::path_to(std::uint32_t index, std::vector<std::uint32_t>& path)
{
	auto path_index = index;
	path.push_back(index);
	while (path_index != start_index_)
	{
		path_index = sequence_map_[path_index];
		path.push_back(path_index);
	}
}

std::int32_t path_finder::distance_to(std::uint32_t index)
{
	return static_cast<std::int32_t>(distance_map_[index]);
}

namespace board_helper
{

template <long unsigned int N>
void calc_helper(const std::array<std::pair<std::int32_t, std::int32_t>, N>& ops,
				 std::uint32_t from_index,
				 std::vector<std::uint32_t>& movements,
				 std::vector<std::uint32_t>& costs,
				 std::int32_t range,
				 bool skip_obstacles) {

	movements.clear();
	costs.clear();

	auto fld = board::to_pos(from_index);
	for (auto&& op : ops) {
		for (std::uint32_t i = 1; i <= range; ++i) {

			auto next_pos = fld;
			next_pos.first += (op.first * i);
			next_pos.second += (op.second * i);

			if (next_pos.first > 0 && next_pos.second > 0
				&& next_pos.first < board::cols_n && next_pos.second < board::rows_n) {
				auto index = board::to_index(next_pos.first, next_pos.second);

				costs.push_back(i);
				movements.push_back(index);

				if (!board::empty(index) && !skip_obstacles)
					break;
			}
		}
	}
}

void calc_straight(std::uint32_t from_index,
				   std::vector<std::uint32_t>& movements,
				   std::vector<std::uint32_t>& costs,
				   std::int32_t range,
				   bool skip_obstacles)
{
	const std::array<std::pair<std::int32_t, std::int32_t>, 4> ops = {
			std::make_pair(-1, 0),
			std::make_pair(+1, 0),
			std::make_pair(0, +1),
			std::make_pair(0, -1)
    };

	calc_helper(ops, from_index, movements, costs, range, skip_obstacles);
}

void calc_diagonal(std::uint32_t from_index,
				   std::vector<std::uint32_t>& movements,
				   std::vector<std::uint32_t>& costs,
				   std::int32_t range,
				   bool skip_obstacles) {

	const std::array<std::pair<std::int32_t, std::int32_t>, 4> ops = {
			std::make_pair(-1, -1),
			std::make_pair(+1, +1),
			std::make_pair(-1, +1),
			std::make_pair(+1, -1)
	};

	calc_helper(ops, from_index, movements, costs, range, skip_obstacles);
}

void calc_directed(std::uint32_t from_index,
				   std::vector<std::uint32_t>& movements,
				   std::vector<std::uint32_t>& costs,
				   std::int32_t range,
				   bool skip_obstacles) {

	const std::array<std::pair<std::int32_t, std::int32_t>, 8> ops = {
			std::make_pair(-1, 0),
			std::make_pair(+1, 0),
			std::make_pair(0, +1),
			std::make_pair(0, -1),
			std::make_pair(-1, -1),
			std::make_pair(+1, +1),
			std::make_pair(-1, +1),
			std::make_pair(+1, -1)
	};

	calc_helper(ops, from_index, movements, costs, range, skip_obstacles);
}

void neighboring_fields(std::uint32_t for_index, std::vector<std::uint32_t>& fields, bool available)
{
	fields.clear();
	auto fld = board::to_pos(for_index);

	for (std::int32_t col = -1; col <= 1; ++col) {
		for (std::int32_t row = -1; row <= 1; ++row)
		{
			auto col_index = fld.first + col;
			auto row_index = fld.second + row;
			auto index = board::to_index(col_index, row_index);
			if ((col || row) && col_index < board::cols_n
				&& row_index < board::rows_n && (!available || board::empty(index)))
			{
				fields.push_back(board::to_index(col_index, row_index));
			}
		}
	}
}

void circle(std::uint32_t for_index, std::vector<std::uint32_t>& fields, bool available) {

	fields.clear();
	auto fld = board::to_pos(for_index);

	for (std::int32_t col = -2; col <= 2; ++col) {
		for (std::int32_t row = -2; row <= 2; ++row) {
			if (abs(col) == 2 || abs(row) == 2) {
				auto col_index = fld.first + col;
				auto row_index = fld.second + row;
				auto index = board::to_index(col_index, row_index);
				if ((col || row) && col_index < board::cols_n
					&& row_index < board::rows_n && (!available || board::empty(index)))
				{
					fields.push_back(board::to_index(col_index, row_index));
				}
			}
		}
	}
}

void all_free(std::vector<std::uint32_t>& fields) {
	for (std::uint32_t index = 0; index < board::rows_n * board::cols_n; ++index) {
		if (board::empty(index)) {
			fields.push_back(index);
		}
	}
}

void all(std::vector<std::uint32_t>& fields) {
	for (std::uint32_t index = 0; index < board::rows_n * board::cols_n; ++index) {
		fields.push_back(index);
	}
}

};