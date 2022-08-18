#pragma once

#include <cstdint>

#include <turn_based/turn_system.h>

struct effect {
  virtual bool set_effect(std::uint32_t entity_id) = 0;
  virtual void remove_effect(std::uint32_t entity_id) = 0;
};

struct base_effect {
  virtual ~base_effect() = default;
};

enum class effect_types { positive, negative };

class applied_effect {
 public:
  applied_effect() = default;
  applied_effect(std::string name, std::string description, effect_types effect_type, bool effect_removable)
      : name_(std::move(name)),
        description_(std::move(description)),
        effect_type_(effect_type),
        effect_removable_(effect_removable) {}

  ~applied_effect() {
    if (on_destruction_) on_destruction_();
  }

  [[nodiscard]] std::string get_name() const { return name_; }

  [[nodiscard]] std::string get_description() const { return description_; }

  [[nodiscard]] effect_types get_effect_type() const { return effect_type_; }

  [[nodiscard]] bool is_effect_removable() const { return effect_removable_; }

  void set_turn_connection(turn_scoped_connection connection) {
    turn_connection_ = std::move(connection);
  }

  template <typename Callback>
  void set_on_destruction(Callback callback) {
    on_destruction_ = callback;
  }

 private:
  std::string name_;
  std::string description_;
  effect_types effect_type_{effect_types::negative};
  bool effect_removable_{false};
  turn_scoped_connection turn_connection_;
  std::function<void()> on_destruction_{nullptr};
};

inline std::shared_ptr<applied_effect> make_negative_effect(std::string name, std::string description = {}) {
  return std::make_shared<applied_effect>(std::move(name), std::move(description), effect_types::negative, true);
}

inline std::shared_ptr<applied_effect> make_positive_effect(std::string name, std::string description = {}) {
  return std::make_shared<applied_effect>(std::move(name), std::move(description), effect_types::positive, true);
}

inline std::shared_ptr<applied_effect> make_not_removable_positive_effect(
    std::string name, std::string description = {}) {
  return std::make_shared<applied_effect>(std::move(name), std::move(description), effect_types::positive, false);
}

inline std::shared_ptr<applied_effect> make_not_removable_negative_effect(
    std::string name, std::string description = {}) {
  return std::make_shared<applied_effect>(std::move(name), std::move(description), effect_types::negative, false);
}
