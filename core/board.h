#ifndef BOARD_H
#define BOARD_H

#include <memory>
#include <functional>
#include <algorithm>
#include <vector>
#include <array>

class board final
{
public:
	static const std::size_t cols_n = 15;
	static const std::size_t rows_n = 10;
	static const std::size_t empty_id = std::numeric_limits<std::size_t>::max();

	inline static void insert(size_t on_index, size_t entity_id)
	{
		fields_[on_index].push_back(entity_id);
	}
	inline static void remove(size_t from_index)
	{
		fields_[from_index].pop_back();
	}
	inline static void move(size_t from_index, size_t to_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		fields_[to_index].push_back(entity_id);
	}
	inline static size_t take(size_t from_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		return entity_id;
	}
	inline static void give_back(size_t entity_id, size_t to_index)
	{
		fields_[to_index].push_back(entity_id);
	}
	inline static size_t at(size_t at_index)
	{
        auto& field = fields_[at_index];
        if (field.empty())
            return empty_id;
		return fields_[at_index].back();
	}
	inline static bool empty(size_t at_index)
	{
		return fields_[at_index].empty();
	}
	inline static size_t index_for(size_t entity_id) {
		auto it = std::find_if(std::begin(fields_), std::end(fields_), [entity_id](auto field) {
			if (field.empty())
				return false;
			return field.back() == entity_id;
		});
		if (it != std::end(fields_))
			return it - std::begin(fields_);
		else
			return empty_id;
	}
	inline static void remove_entity(size_t entity_id)
	{
		for (auto&& field : fields_) {
			auto it = std::remove(std::begin(field), std::end(field), entity_id);
			if (it != std::end(field)) {
				field.erase(it);
				break;
			}
		}
	}
	inline static void call_worker(const std::function<void(size_t entity_id, size_t col, size_t row)>& worker)
	{
		for (size_t i = 0; i < fields_.size(); ++i)
		{
			auto col_row = to_col_row(i);
            if (fields_[i].empty()) {
                worker(empty_id, col_row.first, col_row.second);
            } else {
                for (auto&& id : fields_[i]) {
                    worker(id, col_row.first, col_row.second);
                }
            }
		}
	}
	inline static std::pair<size_t, size_t> to_col_row(size_t index)
	{
		return std::make_pair(index % board::cols_n, index / board::cols_n);
	}
	inline static size_t to_index(size_t col, size_t row)
	{
		return col + row * board::cols_n;
	}
private:
	static std::array<std::vector<std::size_t>, cols_n * rows_n> fields_;
};

#endif