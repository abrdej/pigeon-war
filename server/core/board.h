#ifndef BOARD_H
#define BOARD_H

#include <functional>
#include <algorithm>
#include <vector>
#include <array>
#include <SFML/Config.hpp>

class board final {
public:
	static const sf::Uint64 cols_n = 15;
	static const sf::Uint64 rows_n = 10;
	static const sf::Uint64 empty_id = std::numeric_limits<sf::Uint64>::max();

	inline static void insert(sf::Uint64 on_index, sf::Uint64 entity_id)
	{
		fields_[on_index].push_back(entity_id);
	}
	inline static void remove(sf::Uint64 from_index)
	{
		fields_[from_index].pop_back();
	}
	inline static void move(sf::Uint64 from_index, sf::Uint64 to_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		fields_[to_index].push_back(entity_id);
	}
	inline static sf::Uint64 take(sf::Uint64 from_index)
	{
		auto entity_id = fields_[from_index].back();
		fields_[from_index].pop_back();
		return entity_id;
	}
	inline static sf::Uint64 take_bottom(sf::Uint64 from_index)
	{
		auto entity_id = fields_[from_index].front();
		fields_[from_index].erase(std::begin(fields_[from_index]));
		return entity_id;
	}
	inline static void give_back(sf::Uint64 entity_id, sf::Uint64 to_index)
	{
		fields_[to_index].push_back(entity_id);
	}
	inline static sf::Uint64 at(sf::Uint64 at_index)
	{
        auto& field = fields_[at_index];
        if (field.empty())
            return empty_id;
		return field.back();
	}
	inline static bool empty(sf::Uint64 at_index)
	{
		return fields_[at_index].empty();
	}
	inline static sf::Uint64 index_for(sf::Uint64 entity_id)
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
	inline static void remove_entity(sf::Uint64 entity_id)
	{
		for (auto&& field : fields_) {
			auto it = std::remove(std::begin(field), std::end(field), entity_id);
			if (it != std::end(field)) {
				field.erase(it);
				break;
			}
		}
	}
	inline static void for_each(const std::function<void(sf::Uint64 entity_id, sf::Uint64 col, sf::Uint64 row)>& func) {
		for (sf::Uint64 i = 0; i < fields_.size(); ++i)
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
	inline static std::pair<sf::Uint64, sf::Uint64> to_pos(sf::Uint64 index)
	{
		return std::make_pair(index % board::cols_n, index / board::cols_n);
	}
	inline static sf::Uint64 to_index(sf::Uint64 col, sf::Uint64 row)
	{
		return col + row * board::cols_n;
	}
	inline static bool is_valid(sf::Uint64 col, sf::Uint64 row) {
		return col >= 0 && col < cols_n && row >= 0 && row < rows_n;
	}
    static std::array<std::vector<sf::Uint64>, cols_n * rows_n> fields_;
};

#endif