#include <turn_based/board.h>

#include <turn_based/managers/entity_manager.h>

void board::insert(index_t on_index, entity_id_t entity_id) {
  fields_[on_index.cast()].push_back(entity_id);

  // TODO: we want to register this callback from somewhere else
  game::get<entity_manager>().on_destroy(entity_id,
                                         [this, entity_id]() { remove_entity(entity_id); });

  board_change_signal_();
}

void board::remove(index_t from_index) {
  fields_[from_index.cast()].pop_back();

  board_change_signal_();
}

entity_id_t board::move(index_t from_index, index_t to_index) {
  auto entity_id = fields_[from_index.cast()].back();
  fields_[from_index.cast()].pop_back();
  fields_[to_index.cast()].push_back(entity_id);

  board_change_signal_();

  return entity_id;
}

entity_id_t board::take(index_t from_index) {
  auto entity_id = fields_[from_index.cast()].back();
  fields_[from_index.cast()].pop_back();

  board_change_signal_();

  return entity_id;
}

entity_id_t board::take_bottom(index_t from_index) {
  auto entity_id = fields_[from_index.cast()].front();
  fields_[from_index.cast()].erase(std::begin(fields_[from_index.cast()]));

  board_change_signal_();

  return entity_id;
}

void board::give_back(entity_id_t entity_id, index_t to_index) {
  fields_[to_index.cast()].push_back(entity_id);
  board_change_signal_();
}

entity_id_t board::at(index_t at_index) {
  auto& field = fields_[at_index.cast()];
  if (field.empty()) return null_entity_id;
  return field.back();
}

bool board::empty(index_t at_index) { return fields_[at_index.cast()].empty(); }

index_t board::index_for(entity_id_t entity_id) {
  auto it = std::find_if(std::begin(fields_), std::end(fields_), [entity_id](auto field) {
    if (field.empty()) return false;
    for (auto&& item : field) {
      if (item == entity_id) {
        return true;
      }
    }
    return false;
    // return field.back() == entity_id;
  });
  return it == std::end(fields_) ?
         null_index : index_t{static_cast<index_t::value_type>(it - std::begin(fields_))};
}

void board::remove_entity(entity_id_t entity_id) {
  for (auto& field : fields_) {
    auto it = std::remove(std::begin(field), std::end(field), entity_id);
    if (it != std::end(field)) {
      field.erase(it);
      break;
    }
  }
  board_change_signal_();
}

void board::for_each(const std::function<void(entity_id_t entity_id, std::uint32_t col,
                                              std::uint32_t row)>& func) {
  for (std::uint32_t i = 0; i < fields_.size(); ++i) {
    auto col_row = to_pos(index_t{i});
    if (fields_[i].empty()) {
      func(null_entity_id, col_row.first, col_row.second);
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

std::pair<std::uint32_t, std::uint32_t> board::to_pos(index_t index) {
  return std::make_pair(index.cast() % cols_n, index.cast() / cols_n);
}

index_t board::to_index(std::uint32_t col, std::uint32_t row) { return index_t{col + row * cols_n}; }

bool board::is_valid(std::uint32_t col, std::uint32_t row) {
  return col >= 0 && col < cols_n && row >= 0 && row < rows_n;
}