#pragma once

#include <memory>
#include <typeindex>

#include <turn_based/turn_system.h>
#include <turn_based/base_effect.h>
#include <turn_based/managers/entity_manager.h>

class applied_effects {
 public:
  void put_named(const std::string& effect_name, std::shared_ptr<applied_effect> x) {
    named_data_[effect_name] = std::move(x);
  };

  void destroy_named(const std::string& effect_name) { named_data_.erase(effect_name); }

  bool has(const std::string& effect_name) const {
    return named_data_.find(effect_name) != std::end(named_data_);
  }

  friend void remove_negative_effects(entity_id_t);
  friend std::unordered_map<entity_id_t, std::vector<std::string>> get_effects();

 private:
  std::unordered_map<std::string, std::shared_ptr<applied_effect>> named_data_;
};

inline void add_effect(entity_id_t entity_id, const std::shared_ptr<applied_effect>& x) {
  auto applied_effects_ptr = game::get<entity_manager>().get(entity_id).get<applied_effects>();
  if (applied_effects_ptr) {
    applied_effects_ptr->put_named(x->get_name(), x);
  }
}

inline void remove_effect(entity_id_t entity_id, const std::string& effect_name) {
  game::get<entity_manager>().get(entity_id).get<applied_effects>()->destroy_named(effect_name);
}

inline bool has_effect(entity_id_t entity_id, const std::string& effect_name) {
  return game::get<entity_manager>().get(entity_id).get<applied_effects>()->has(effect_name);
}

void remove_negative_effects(entity_id_t entity_id);

std::unordered_map<entity_id_t, std::vector<std::string>> get_effects();
