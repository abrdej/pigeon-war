#pragma once

#include <functional>
#include <turn_based/ability.h>

/**
 * @brief Base class for moving abilities.
 */
class move_ability : public active_ability {
  using move_callback_type = std::function<void(index_t, index_t, std::int32_t)>;

 protected:
  explicit move_ability(std::string name) : active_ability(std::move(name)) {}

  void call_move_callbacks(index_t from_index, index_t to_index, std::int32_t cost) {
    for (const auto& callback_pack : move_callbacks_) {
      callback_pack.second(from_index, to_index, cost);
    }
  }

 public:
  ability_types type() const override {
    return ability_types::moving;
  }

  virtual void refresh_range() = 0;
  virtual bool has_range() const = 0;
  virtual void remove_range() = 0;
  virtual void set_slow_down(std::int32_t value) = 0;
  virtual void remove_slow_down() = 0;

  virtual std::uint32_t set_move_callback(move_callback_type callback) {
    static std::uint32_t callback_id_gen = 0;
    move_callbacks_.emplace(callback_id_gen, std::move(callback));
    return callback_id_gen++;
  }
  virtual void remove_move_callback(std::uint32_t callback_id) {
    move_callbacks_.erase(callback_id);
  }

 private:
  std::unordered_map<std::uint32_t, move_callback_type> move_callbacks_;
};
