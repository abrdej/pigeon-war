#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include <boost/dll/shared_library.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/function.hpp>

#include <turn_based/entity.h>
#include <turn_based/messages/messages_makers.h>
#include <turn_based/sender.h>

class entity_manager final {
  std::unordered_map<std::uint32_t, base_entity> entities;
  std::unordered_map<std::uint32_t, std::vector<std::function<void()>>> on_destroy_callbacks;

  inline std::uint32_t generate_id() {
    static std::uint32_t entity_id_generator = 0;
    return entity_id_generator++;
  }

 public:
  inline std::uint32_t create(std::function<void(base_entity& entity)> creator) {
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

  template <typename EntityFactory>
  inline std::uint32_t create() {
    auto entity_id = generate_id();
    auto& entity = entities.emplace(entity_id, base_entity()).first->second;
    entity.entity_id = entity_id;
    EntityFactory::create(entity);
    return entity_id;
  }

  base_entity get(std::uint32_t entity_id) {
    return entities.at(entity_id);
  }

  inline bool alive(std::uint32_t entity_id) {
    return entities.find(entity_id) != std::end(entities);
  }

  inline void destroy(std::uint32_t entity_id) {
    entities.erase(entity_id);

    sender::send(make_remove_entity_message(entity_id));

    call_destroy_callbacks(entity_id);
  }

  void on_destroy(std::uint32_t entity_id, std::function<void()> callback) {
    on_destroy_callbacks[entity_id].push_back(std::move(callback));
  }

  void call_destroy_callbacks(std::uint32_t entity_id) {
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
