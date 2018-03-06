#ifndef BOARD_H
#define BOARD_H

#include <functional>
#include <algorithm>
#include <vector>
#include <array>
#include <boost/signals2.hpp>
#include <SFML/Config.hpp>

class board final {
public:
	static const std::uint32_t cols_n = 15;
	static const std::uint32_t rows_n = 10;
	static const std::uint32_t empty_id = std::numeric_limits<std::uint32_t>::max();

	using board_change_signal_type = boost::signals2::signal<void()>;
	static board_change_signal_type board_change_signal;

	template <typename SlotType>
	static void on_change(SlotType x) {
		board_change_signal.connect(x);
	}

	inline static void insert(std::uint32_t on_index, std::uint32_t entity_id)
	{
		fields_[on_index].push_back(entity_id);

		board_change_signal();
	}
	inline static void remove(std::uint32_t from_index)
	{
		fields_[from_index].pop_back();

		board_change_signal();
	}
	inline static void move(std::uint32_t from_index, std::uint32_t to_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		fields_[to_index].push_back(entity_id);

		board_change_signal();
	}
	inline static std::uint32_t take(std::uint32_t from_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();

		board_change_signal();

		return entity_id;
	}
	inline static std::uint32_t take_bottom(std::uint32_t from_index)
	{
		auto entity_id = fields_[from_index].front();
		fields_[from_index].erase(std::begin(fields_[from_index]));

		board_change_signal();

		return entity_id;
	}
	inline static void give_back(std::uint32_t entity_id, std::uint32_t to_index)
	{
		fields_[to_index].push_back(entity_id);
		board_change_signal();
	}
	inline static std::uint32_t at(std::uint32_t at_index)
	{
        auto& field = fields_[at_index];
        if (field.empty())
            return empty_id;
		return field.back();
	}
	inline static bool empty(std::uint32_t at_index)
	{
		return fields_[at_index].empty();
	}
	inline static std::uint32_t index_for(std::uint32_t entity_id)
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
	inline static void remove_entity(std::uint32_t entity_id)
	{
		for (auto&& field : fields_) {
			auto it = std::remove(std::begin(field), std::end(field), entity_id);
			if (it != std::end(field)) {
				field.erase(it);
				break;
			}
		}

		board_change_signal();
	}
	inline static void for_each(const std::function<void(std::uint32_t entity_id, std::uint32_t col, std::uint32_t row)>& func) {
		for (std::uint32_t i = 0; i < fields_.size(); ++i)
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
	inline static std::pair<std::uint32_t, std::uint32_t> to_pos(std::uint32_t index)
	{
		return std::make_pair(index % board::cols_n, index / board::cols_n);
	}
	inline static std::uint32_t to_index(std::uint32_t col, std::uint32_t row)
	{
		return col + row * board::cols_n;
	}
	inline static bool is_valid(std::uint32_t col, std::uint32_t row) {
		return col >= 0 && col < cols_n && row >= 0 && row < rows_n;
	}
    static std::array<std::vector<std::uint32_t>, cols_n * rows_n> fields_;
};

namespace std {
template <typename CharT>
basic_ostream<CharT>& operator<<(basic_ostream<CharT>& os, const pair<uint32_t, uint32_t>& pos)
{
	os << "(" << pos.first << ", " << pos.second << ")";
	return os;
}
} // std

#endif