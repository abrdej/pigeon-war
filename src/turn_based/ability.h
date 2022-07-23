#pragma once

#include <functional>
#include <iostream>
#include <typeinfo>
#include <unordered_map>

#include <turn_based/bitmap_key.h>
#include <turn_based/configurable.h>
#include <turn_based/hint_configuration.h>
#include <turn_based/utils/descriptions.h>

/**
 * Base class for all abilities.
 * Abilities can be active or passive.
 */

enum class ability_types {
  moving = 0, offensive, special, defensive, passive, not_defined
};

struct ability_interface {
  [[nodiscard]] virtual std::string hint() const = 0;
  [[nodiscard]] virtual ability_types type() const = 0;
  [[nodiscard]] virtual bool usable() const = 0;
  [[nodiscard]] virtual std::string get_name() const = 0;
  virtual ~ability_interface() = default;
};

struct active_ability_interface {
  virtual void prepare(std::uint32_t for_index) = 0;
  virtual ~active_ability_interface() = default;
};

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

  [[nodiscard]] bitmap_key get_name() const override {
    return name_;
  }

 private:
  std::string name_;
};

struct active_ability : ability {
  active_ability() = default;
  explicit active_ability(std::string name) : ability(std::move(name)) {}
  virtual void prepare(std::uint32_t for_index) = 0;
};

struct passive_ability : ability {
  passive_ability() = default;
  explicit passive_ability(std::string name) : ability(std::move(name)) {}
  ability_types type() const override {
    return ability_types::passive;
  }
};

struct ranged_ability : active_ability {
  ranged_ability() = default;
  explicit ranged_ability(std::string name) : active_ability(std::move(name)) {}
  std::int32_t range{0};
};

inline void try_prepare_ability(ability& x, std::uint32_t for_index) {
  try {
    dynamic_cast<active_ability&>(x).prepare(for_index);
  } catch (std::bad_cast&) {}
}

#define MOVING_ABILITY() \
ability_types type() const override { \
    return ability_types::moving; \
}

#define ABILITY_TYPE(ability_type) \
ability_types type() const override { \
    return ability_types::ability_type; \
}

#define ADD_BITMAP_GETTER(bitmap) \
bitmap_key get_name() const override { \
    return #bitmap; \
}
