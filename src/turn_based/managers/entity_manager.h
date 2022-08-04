#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <boost/dll/shared_library.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/function.hpp>

#include <turn_based/entity.h>
#include <turn_based/defs.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>

class entity_manager final {
  std::unordered_map<entity_id_t, base_entity> entities;
  std::unordered_map<entity_id_t, std::vector<std::function<void()>>> on_destroy_callbacks;

  static entity_id_t generate_id() {
    static entity_id_t entity_id_generator{0};
    entity_id_generator = entity_id_t{static_cast<entity_id_t::value_type>(entity_id_generator) + 1};
    return entity_id_generator;
  }

 public:
  inline entity_id_t create(std::function<void(base_entity& entity)> creator) {
    auto entity_id = generate_id();
    auto& entity = entities.emplace(entity_id, base_entity()).first->second;
    entity.entity_id = entity_id;
    creator(entity);
    return entity_id;
  }

  void clear() {
    entities.clear();
    on_destroy_callbacks.clear();
  }

  base_entity get(entity_id_t entity_id) {
    return entities.at(entity_id);
  }

  inline bool alive(entity_id_t entity_id) {
    return entities.find(entity_id) != std::end(entities);
  }

  inline void destroy(entity_id_t entity_id) {
    entities.erase(entity_id);

    sender::send(make_remove_entity_message(entity_id));

    call_destroy_callbacks(entity_id);
  }

  void on_destroy(entity_id_t entity_id, std::function<void()> callback) {
    on_destroy_callbacks[entity_id].push_back(std::move(callback));
  }

  void call_destroy_callbacks(entity_id_t entity_id) {
    auto it = on_destroy_callbacks.find(entity_id);
    if (it != std::end(on_destroy_callbacks)) {
      for (auto&& callback : it->second)
        callback();
      on_destroy_callbacks.erase(it);
    }
  }

  template <typename Function>
  void for_all(Function function) {
    for (auto&& entity_pack : entities) {
      function(entity_pack.second);
    }
  }
};
