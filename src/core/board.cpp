#include "board.h"

void board::insert(std::uint32_t on_index, std::uint32_t entity_id)
{
    fields_[on_index].push_back(entity_id);

    game::get<entity_manager>().on_destroy(entity_id, [this, entity_id]() {
        remove_entity(entity_id);
    });

    board_change_signal();
}

void board::remove(std::uint32_t from_index)
{
    fields_[from_index].pop_back();

    board_change_signal();
}

std::uint32_t board::move(std::uint32_t from_index, std::uint32_t to_index)
{
    auto entity_id = fields_[from_index].back();
    fields_[from_index].pop_back();
    fields_[to_index].push_back(entity_id);

    board_change_signal();

    return entity_id;
}

std::uint32_t board::take(std::uint32_t from_index)
{
    auto entity_id = fields_[from_index].back();
    fields_[from_index].pop_back();

    board_change_signal();

    return entity_id;
}

std::uint32_t board::take_bottom(std::uint32_t from_index)
{
    auto entity_id = fields_[from_index].front();
    fields_[from_index].erase(std::begin(fields_[from_index]));

    board_change_signal();

    return entity_id;
}

void board::give_back(std::uint32_t entity_id, std::uint32_t to_index)
{
    fields_[to_index].push_back(entity_id);
    board_change_signal();
}

std::uint32_t board::at(std::uint32_t at_index)
{
    auto& field = fields_[at_index];
    if (field.empty())
        return empty_id;
    return field.back();
}

bool board::empty(std::uint32_t at_index)
{
    return fields_[at_index].empty();
}

std::uint32_t board::index_for(std::uint32_t entity_id)
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

void board::remove_entity(std::uint32_t entity_id)
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

void board::for_each(const std::function<void(std::uint32_t entity_id, std::uint32_t col, std::uint32_t row)>& func) {
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

void board::set_size(std::uint32_t cols, std::uint32_t rows) {
    cols_n = cols;
    rows_n = rows;
    fields_.resize(cols_n * rows_n);
}

std::pair<std::uint32_t, std::uint32_t> board::to_pos(std::uint32_t index)
{
    return std::make_pair(index % cols_n, index / cols_n);
}
std::uint32_t board::to_index(std::uint32_t col, std::uint32_t row)
{
    return col + row * cols_n;
}

bool board::is_valid(std::uint32_t col, std::uint32_t row) {
    return col >= 0 && col < cols_n && row >= 0 && row < rows_n;
}