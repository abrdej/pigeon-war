#include "path_finder.h"
#include "board.h"
#include "abilities/moveable.h"

path_finder::path_finder(bool all_fields)
		: start_index_(-1)
{
	board::for_each([this, &all_fields](size_t entity_id, size_t col, size_t row) {
		auto rows_n = board::rows_n;
		auto cols_n = board::cols_n;
		auto key_from = board::to_index(col, row);

		if (row < rows_n - 1) {
			auto key_to = board::to_index(col, row + 1);
			if (board::empty(key_to) || all_fields)
				graph_.add_egde(key_from, key_to);

			if (board::empty(key_from) || all_fields)
				graph_.add_egde(key_to, key_from);
		}
		if (col < cols_n - 1) {
			auto key_to = board::to_index(col + 1, row);
			if (board::empty(key_to) || all_fields)
				graph_.add_egde(key_from, key_to);

			if (board::empty(key_from) || all_fields)
				graph_.add_egde(key_to, key_from);
		}
	});
}

void path_finder::calc(size_t from_index)
{
	start_index_ = from_index;
	distance_map_.clear();
	sequence_map_.clear();
	breadth_search(graph_, from_index, distance_map_, sequence_map_);
}

size_t path_finder::find_first_satisfy_conditions(size_t from_index, const std::function<bool(size_t)>& condition_fn)
{
	start_index_ = from_index;
	distance_map_.clear();
	sequence_map_.clear();
	return breadth_search(graph_, from_index, distance_map_, sequence_map_, condition_fn);
}

void path_finder::get_possible_movements(std::vector<size_t>& movements, std::vector<size_t>& costs, int range)
{
	movements.clear();
	costs.clear();
	for (auto& elem : distance_map_)
		if (elem.second <= range && elem.second != 0)
		{
			movements.emplace_back(elem.first);
			costs.emplace_back(elem.second);
		}
}

void path_finder::path_to(size_t index, std::vector<size_t>& path)
{
	auto path_index = index;
	path.push_back(index);
	while (path_index != start_index_)
	{
		path_index = sequence_map_[path_index];
		path.push_back(path_index);
	}
}

size_t path_finder::distance_to(size_t index)
{
	auto it = distance_map_.find(index);
	if (it != std::end(distance_map_))
		return it->second;
	return -1;
}

namespace board_helper
{
void calc_straight(size_t from_index, std::vector<size_t>& movements, std::vector<size_t>& costs, int range, bool skip_obstacles)
{
	movements.clear();
	costs.clear();

	auto fld = board::to_pos(from_index);
	for (size_t i = fld.first - 1; i != -1; --i)
	{
		auto cost = fld.first - i;
		if (cost > range)
			break;
		auto index = board::to_index(i, fld.second);

		costs.push_back(cost);
		movements.push_back(index);

		if (!board::empty(index) && !skip_obstacles)
			break;
	}

	for (size_t i = fld.first + 1; i < board::cols_n; ++i)
	{
		auto cost = i - fld.first;
		if (cost > range)
			break;

		auto index = board::to_index(i, fld.second);

		costs.push_back(cost);
		movements.push_back(index);

		if (!board::empty(index) && !skip_obstacles)
			break;
	}

	for (size_t i = fld.second - 1; i != -1; --i)
	{
		auto cost = fld.second - i;
		if (cost > range)
			break;

		auto index = board::to_index(fld.first, i);

		costs.push_back(cost);
		movements.push_back(index);

		if (!board::empty(index) && !skip_obstacles)
			break;
	}

	for (size_t i = fld.second + 1; i < board::rows_n; ++i)
	{
		auto cost = i - fld.second;
		if (cost > range)
			break;

		auto index = board::to_index(fld.first, i);

		costs.push_back(cost);
		movements.push_back(index);

		if (!board::empty(index) && !skip_obstacles)
			break;
	}
}

void neighboring_fields(size_t for_index, std::vector<size_t>& fields, bool available)
{
	fields.clear();
	auto fld = board::to_pos(for_index);

	for (int col = -1; col <= 1; ++col)
		for (int row = -1; row <= 1; ++row)
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

void all_free(std::vector<size_t>& fields) {
	for (size_t index = 0; index < board::rows_n * board::cols_n; ++index) {
		if (board::empty(index)) {
			fields.push_back(index);
		}
	}
}

};