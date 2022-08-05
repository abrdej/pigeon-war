#pragma once

#include <string>

#include <turn_based/configurable.h>
#include <turn_based/defs.h>
#include <turn_based/hint_configuration.h>
#include <turn_based/utils/descriptions.h>

/**
 * @brief Defines the ability type.
 */
enum class ability_types {
  moving = 0, offensive, special, defensive, passive, not_defined
};

/**
 * @brief Interface for all abilities.
 */
struct ability_interface {
  [[nodiscard]] virtual std::string hint() const = 0;
  [[nodiscard]] virtual ability_types type() const = 0;
  [[nodiscard]] virtual bool usable() const = 0;
  [[nodiscard]] virtual std::string get_name() const = 0;
  virtual ~ability_interface() = default;
};

/**
 * @brief Interface for active abilities.
 */
struct active_ability_interface {
  virtual void prepare(index_t for_index) = 0;
  virtual ~active_ability_interface() = default;
};

/**
 * @brief Base class for all abilities, provides some core functionality, like configuration, hint, etc.
 */
class ability : public ability_interface, protected configurable, protected hint_configuration {
 protected:
  ability() = default;
  explicit ability(std::string name) : name_(std::move(name)) {
    configurable::initialize(name_);
  }

  ~ability() override = default;

 public:
  [[nodiscard]] std::string hint() const override {
    return hint_configuration::get_hint();
  }

  [[nodiscard]] ability_types type() const override {
    return ability_types::not_defined;
  }

  [[nodiscard]] bool usable() const override {
    return type() == ability_types::passive;
  }

  [[nodiscard]] std::string get_name() const override {
    return name_;
  }

 private:
  std::string name_;
};

/**
 * @brief Base class for active abilities.
 */
struct active_ability : ability, active_ability_interface {
  active_ability() = default;
  explicit active_ability(std::string name) : ability(std::move(name)) {}
};

/**
 * @brief Base class for passive abilities.
 */
struct passive_ability : ability {
  passive_ability() = default;
  explicit passive_ability(std::string name) : ability(std::move(name)) {}
  [[nodiscard]] ability_types type() const override {
    return ability_types::passive;
  }
};

/**
 * @brief Base class for abilities with a range.
 */
struct ranged_ability : active_ability {
  ranged_ability() = default;
  explicit ranged_ability(std::string name) : active_ability(std::move(name)) {}
  std::int32_t range{0};
};

/**
 * @brief Prepares the ability unless its passive.
 */
inline void try_prepare_ability(ability& x, index_t for_index) {
  try {
    dynamic_cast<active_ability_interface&>(x).prepare(for_index);
  } catch (std::bad_cast&) {}
}
