#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include <turn_based/entity.h>
#include <turn_based/defs.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>

/**
 * @brief Responsible to manage entities.
 */
class entity_manager final {
 public:
  entity_id_t create(const std::function<void(base_entity& entity)>& creator) {
    auto entity_id = generate_id();
    auto& entity = entities_.emplace(entity_id, base_entity()).first->second;
    entity.entity_id = entity_id;
    creator(entity);
    return entity_id;
  }

  base_entity get(entity_id_t entity_id) {
    return entities_.at(entity_id);
  }

  bool alive(entity_id_t entity_id) {
    return entities_.find(entity_id) != std::end(entities_);
  }

  void destroy(entity_id_t entity_id) {
    entities_.erase(entity_id);
    sender::send(make_remove_entity_message(entity_id));
    call_destroy_callbacks(entity_id);
  }

  void on_destroy(entity_id_t entity_id, std::function<void()> callback) {
    on_destroy_callbacks_[entity_id].push_back(std::move(callback));
  }

  void call_destroy_callbacks(entity_id_t entity_id) {
    auto it = on_destroy_callbacks_.find(entity_id);
    if (it != std::end(on_destroy_callbacks_)) {
      for (const auto& callback : it->second) {
        callback();
      }
      on_destroy_callbacks_.erase(it);
    }
  }

  void clear() {
    entities_.clear();
    on_destroy_callbacks_.clear();
  }

  template <typename Function>
  void for_all(Function function) {
    for (const auto& entity_pack : entities_) {
      function(entity_pack.second);
    }
  }

 private:
  static entity_id_t generate_id() {
    static entity_id_t entity_id_generator{0};
    entity_id_generator = entity_id_t{static_cast<entity_id_t::value_type>(entity_id_generator) + 1};
    return entity_id_generator;
  }

  std::unordered_map<entity_id_t, base_entity> entities_;
  std::unordered_map<entity_id_t, std::vector<std::function<void()>>> on_destroy_callbacks_;
};
