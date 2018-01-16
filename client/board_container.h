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
#include "common/define_packet.h"

class board_container final {
public:
	static const std::uint64_t cols_n = 15;
	static const std::uint64_t rows_n = 10;
	static const std::uint64_t empty_id = std::numeric_limits<std::uint64_t>::max();

	inline void insert(std::uint64_t on_index, std::uint64_t entity_id)
	{
		fields_[on_index].push_back(entity_id);
	}
	inline void remove(std::uint64_t from_index)
	{
		fields_[from_index].pop_back();
	}
	inline void move(std::uint64_t from_index, std::uint64_t to_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		fields_[to_index].push_back(entity_id);
	}
	inline std::uint64_t take(std::uint64_t from_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		return entity_id;
	}
	inline std::uint64_t take_bottom(std::uint64_t from_index)
	{
		auto entity_id = fields_[from_index].front();
		fields_[from_index].erase(std::begin(fields_[from_index]));
		return entity_id;
	}
	inline void give_back(std::uint64_t entity_id, std::uint64_t to_index)
	{
		fields_[to_index].push_back(entity_id);
	}
	inline std::uint64_t at(std::uint64_t at_index)
	{
        auto& field = fields_[at_index];
        if (field.empty())
            return empty_id;
		return field.back();
	}
	inline bool empty(std::uint64_t at_index)
	{
		return fields_[at_index].empty();
	}
	inline std::uint64_t index_for(std::uint64_t entity_id)
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
	inline void remove_entity(std::uint64_t entity_id)
	{
		for (auto&& field : fields_) {
			auto it = std::remove(std::begin(field), std::end(field), entity_id);
			if (it != std::end(field)) {
				field.erase(it);
				break;
			}
		}
	}
	inline void for_each(const std::function<void(std::uint64_t entity_id, std::uint64_t col, std::uint64_t row)>& func) {
		for (std::uint64_t i = 0; i < fields_.size(); ++i)
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
	inline std::pair<std::uint64_t, std::uint64_t> to_pos(std::uint64_t index)
	{
		return std::make_pair(index % board_container::cols_n, index / board_container::cols_n);
	}
	inline static std::uint64_t to_index(std::uint64_t col, std::uint64_t row)
	{
		return col + row * board_container::cols_n;
	}
	inline bool is_valid(std::uint64_t col, std::uint64_t row) {
		return col >= 0 && col < cols_n && row >= 0 && row < rows_n;
	}
    std::array<std::vector<std::uint64_t>, cols_n * rows_n> fields_;
};

PACKET_DEFINE1(board_container, fields_)

#endif //PIGEONWAR_BOARD_CONTAINER_H
