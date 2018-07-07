#ifndef BOARD_H
#define BOARD_H

#include <functional>
#include <algorithm>
#include <vector>
#include <array>
#include <boost/signals2.hpp>
#include <messages/make_message.h>
#include <sender.h>
#include <managers/entity_manager.h>
#include "game.h"

class board final {
public:
	static const std::uint32_t empty_id = std::numeric_limits<std::uint32_t>::max();

	using board_change_signal_type = boost::signals2::signal<void()>;
	board_change_signal_type board_change_signal;

	template <typename SlotType>
	void on_change(SlotType x) {
		board_change_signal.connect(x);
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

namespace std {
template <typename CharT>
basic_ostream<CharT>& operator<<(basic_ostream<CharT>& os, const pair<uint32_t, uint32_t>& pos)
{
	os << "(" << pos.first << ", " << pos.second << ")";
	return os;
}
} // namespace std

#endif