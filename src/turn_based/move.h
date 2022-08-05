#pragma once

#include <functional>

#include <turn_based/ability.h>
#include <turn_based/turn_system.h>
#include <turn_based/base_effect.h>

class moveable_base : public active_ability {
  using move_callback_type = std::function<void(index_t, index_t, std::int32_t)>;

 protected:
  explicit moveable_base(std::string name) : active_ability(std::move(name)) {}

  void call_move_callbacks(index_t from_index, index_t to_index, std::int32_t cost) {
    for (auto&& callback_pack : move_callbacks_) {
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
  std::unordered_map<std::uint32_t, moveable_base::move_callback_type> move_callbacks_;
};

class move final : public moveable_base, turn_callback_helper {
 public:
  enum class types { path, straight };
  explicit move(std::int32_t range, types type = types::path);

  void refresh_range() override { used_ = false; }

  bool has_range() const override { return !used_; }

  void remove_range() override { used_ = true; }

  void set_slow_down(std::int32_t value) override { range_ = value; }
  void remove_slow_down() override { range_ = base_range_; }

  bool usable() const override { return has_range(); }

  void skip_collisions(bool value) { skip_collisions_ = value; }

 private:
  void prepare(index_t for_index) override;
  void do_move(index_t index_to);

 private:
  static constexpr auto name = "move";

  std::int32_t range_;
  const std::int32_t base_range_;
  bool used_{false};
  bool skip_collisions_{false};
  types movement_type_;
};
