//
// Created by abrdej on 20.12.17.
//

#ifndef PIGEONWAR_BOARD_CONTAINER_H
#define PIGEONWAR_BOARD_CONTAINER_H

#include <array>
#include <vector>
#include <algorithm>
#include <functional>
#include <limits>
#include <rpc/msgpack.hpp>

class board_container final {
public:
	static const std::size_t cols_n = 15;
	static const std::size_t rows_n = 10;
	static const std::size_t empty_id = std::numeric_limits<std::size_t>::max();

	inline void insert(size_t on_index, size_t entity_id)
	{
		fields_[on_index].push_back(entity_id);
	}
	inline void remove(size_t from_index)
	{
		fields_[from_index].pop_back();
	}
	inline void move(size_t from_index, size_t to_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		fields_[to_index].push_back(entity_id);
	}
	inline size_t take(size_t from_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		return entity_id;
	}
	inline size_t take_bottom(size_t from_index)
	{
		auto entity_id = fields_[from_index].front();
		fields_[from_index].erase(std::begin(fields_[from_index]));
		return entity_id;
	}
	inline void give_back(size_t entity_id, size_t to_index)
	{
		fields_[to_index].push_back(entity_id);
	}
	inline size_t at(size_t at_index)
	{
        auto& field = fields_[at_index];
        if (field.empty())
            return empty_id;
		return field.back();
	}
	inline bool empty(size_t at_index)
	{
		return fields_[at_index].empty();
	}
	inline size_t index_for(size_t entity_id)
	{
		auto it = std::find_if(std::begin(fields_), std::end(fields_), [entity_id](auto field){
            if (field.empty())
                return false;
            for (auto&& item : field) {
                if (item == entity_id) {
                    return true;
                }
            }
            return false;
			//return field.back() == entity_id;
		});
		if (it != std::end(fields_))
			return it - std::begin(fields_);
		else
			return empty_id;
	}
	inline void remove_entity(size_t entity_id)
	{
		for (auto&& field : fields_) {
			auto it = std::remove(std::begin(field), std::end(field), entity_id);
			if (it != std::end(field)) {
				field.erase(it);
				break;
			}
		}
	}
	inline void for_each(const std::function<void(size_t entity_id, size_t col, size_t row)>& func) {
		for (size_t i = 0; i < fields_.size(); ++i)
		{
			auto col_row = to_pos(i);
            if (fields_[i].empty()) {
                func(empty_id, col_row.first, col_row.second);
            } else {
                for (auto&& id : fields_[i]) {
                    func(id, col_row.first, col_row.second);
                }
            }
		}
	}
	inline std::pair<size_t, size_t> to_pos(size_t index)
	{
		return std::make_pair(index % board_container::cols_n, index / board_container::cols_n);
	}
	inline static size_t to_index(size_t col, size_t row)
	{
		return col + row * board_container::cols_n;
	}
	inline bool is_valid(std::size_t col, std::size_t row) {
		return col >= 0 && col < cols_n && row >= 0 && row < rows_n;
	}
    std::array<std::vector<std::size_t>, cols_n * rows_n> fields_;

	MSGPACK_DEFINE(fields_);
};

#endif //PIGEONWAR_BOARD_CONTAINER_H
