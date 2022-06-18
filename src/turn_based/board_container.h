#pragma once

#include <deque>
#include <functional>
#include <limits>
#include <vector>

#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

namespace turn_based {

template <typename T, T EmptyValue>
class board_container {
 public:
  using value_type = T;
  using index_type = std::uint32_t;
  using pos_type = std::pair<index_type, index_type>;

  static const value_type empty_value = EmptyValue;
  static const index_type no_index = std::numeric_limits<index_type>::max();

  board_container() = default;

  board_container(index_type cols, index_type rows) : cols_(cols), rows_(rows) {
    fields_.resize(cols * rows);
  }

  void insert(index_type on_index, value_type entity_id) {
    fields_[on_index].push_back(entity_id);
  }
  void insert_bottom(index_type on_index, value_type entity_id) {
    fields_[on_index].push_front(entity_id);
  }
  void remove(index_type from_index) { fields_[from_index].pop_back(); }
  void remove_bottom(index_type from_index) { fields_[from_index].pop_front(); }
  void remove_each(index_type from_index) { fields_[from_index].clear(); }

  void move(index_type from_index, index_type to_index) {
    auto entity_id = fields_[from_index].back();
    fields_[from_index].pop_back();
    fields_[to_index].push_back(entity_id);
  }
  void move_each(index_type from_index, index_type to_index) {
    auto& target_field = fields_[to_index];
    if (target_field.empty()) {
      fields_[to_index] = std::move(fields_[from_index]);
    } else {
      for (const auto& id : fields_[from_index]) {
        fields_[to_index].push_back(id);
      }
      fields_[from_index].clear();
    }
  }

  value_type take(index_type from_index) {
    auto entity_id = fields_[from_index].back();
    fields_[from_index].pop_back();
    return entity_id;
  }
  value_type take_bottom(index_type from_index) {
    auto entity_id = fields_[from_index].front();
    fields_[from_index].pop_front();
    return entity_id;
  }
  auto take_each(index_type from_index) {
    return std::move(fields_[from_index]);
  }

  [[nodiscard]] value_type at(index_type at_index) {
    auto& field = fields_[at_index];
    if (field.empty()) return empty_value;
    return field.back();
  }
  [[nodiscard]] auto& each_at(index_type for_index) {
    return fields_[for_index];
  }
  [[nodiscard]] const auto& each_at(index_type for_index) const {
    return fields_[for_index];
  }

  [[nodiscard]] bool empty_at(index_type at_index) { return fields_[at_index].empty(); }

  index_type index_for(value_type entity_id) {
    auto it = boost::range::find_if(fields_, [entity_id](auto field) {
      if (field.empty()) return false;
      return boost::algorithm::any_of_equal(field, entity_id);
    });
    return it != std::end(fields_) ? std::distance(std::begin(fields_), it) : no_index;
  }

  void remove_entity(value_type entity_id) {
    for (auto& field : fields_) {
      boost::range::remove_erase(field, entity_id);
    }
  }

  void for_each(const std::function<void(value_type entity_id, index_type col, index_type row)>& func) {
    for (index_type i = 0; i < fields_.size(); ++i) {
      auto col_row = to_pos(i);
      if (fields_[i].empty()) {
        func(empty_value, col_row.first, col_row.second);
      } else {
        for (auto&& id : fields_[i]) {
          func(id, col_row.first, col_row.second);
        }
      }
    }
  }

  [[nodiscard]] index_type cols() const {
    return cols_;
  }

  [[nodiscard]] index_type rows() const {
    return rows_;
  }

  [[nodiscard]] pos_type to_pos(index_type index) const {
    return std::make_pair(index % board_container::cols_, index / board_container::cols_);
  }

  [[nodiscard]] index_type to_index(index_type col, index_type row) const { return col + row * cols_; }

  [[nodiscard]] bool is_valid(index_type col, index_type row) const {
    return col >= 0 && col < cols_ && row >= 0 && row < rows_;
  }

 private:
  index_type cols_{0};
  index_type rows_{0};
  std::vector<std::deque<value_type>> fields_;
};

}  // namespace turn_based
