#pragma once

#include <initializer_list>
#include <memory>
#include <vector>

#include <turn_based/event_center.h>
#include <turn_based/game.h>
#include <turn_based/managers/entity_manager.h>

template <typename Callback>
void if_any_die(std::initializer_list<std::uint32_t> entities_id, Callback callback) {
  auto any_die = [callback]() {
    callback();
  };
  for (auto&& entity_id : entities_id) {
    game::get<entity_manager>().on_destroy(entity_id, any_die);
  }
}

template <typename Callback>
void if_any_die(std::vector<std::uint32_t> entities_id, Callback callback) {
  auto any_die = [callback]() {
    callback();
  };
  for (auto&& entity_id : entities_id) {
    game::get<entity_manager>().on_destroy(entity_id, any_die);
  }
}

template <typename Callback>
void if_all_die(std::initializer_list<std::uint32_t> entities_ids, Callback callback) {
  auto entities_ids_ptr = std::make_shared<std::unordered_set<std::uint32_t>>();

  auto someone_die = [callback, entities_ids_ptr](std::uint32_t entity_id) mutable {
    entities_ids_ptr->erase(entity_id);
    if (entities_ids_ptr->empty()) {
      callback();
    }
  };

  for (auto&& entity_id : entities_ids) {
    entities_ids_ptr->insert(entity_id);
    game::get<entity_manager>().on_destroy(entity_id, std::bind(someone_die, entity_id));
  }
}

template <typename Callback>
void if_all_die(std::vector<std::uint32_t> entities_ids, Callback callback) {
  auto entities_ids_ptr = std::make_shared<std::unordered_set<std::uint32_t>>();

  auto someone_die = [callback, entities_ids_ptr](std::uint32_t entity_id) mutable {
    entities_ids_ptr->erase(entity_id);
    if (entities_ids_ptr->empty()) {
      callback();
    }
  };

  for (auto&& entity_id : entities_ids) {
    entities_ids_ptr->insert(entity_id);
    game::get<entity_manager>().on_destroy(entity_id, std::bind(someone_die, entity_id));
  }
}

template <typename Callback>
void on_intro(Callback callback) {
  game::get<event_center>().register_on(events::CLIENT_ACCEPTED, callback);
}
