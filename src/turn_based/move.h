#pragma once

#include <turn_based/move_ability.h>
#include <turn_based/turn_system.h>

/**
 * @brief Standard ability to move the entity.
 */
class move final : public move_ability, turn_callback_helper {
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
