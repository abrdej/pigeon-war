#pragma once

#include <string>
#include <unordered_map>

#include <boost/any.hpp>

#include <turn_based/defs.h>

namespace ai {

class knowledge_box {
 public:
  template <typename T>
  T get(const std::string& key) {
    return boost::any_cast<T>(data_.at(key));
  }

  bool has(const std::string& key) const { return data_.count(key) != 0; }

  template <typename T>
  void insert(const std::string& key, const T& x) {
    data_[key] = x;
  }

 private:
  std::unordered_map<std::string, boost::any> data_;
};

struct ai_knowledge {
 public:
  knowledge_box& global() { return global_knowledge_box_; }

  knowledge_box& player(id_t player_id) { return players_knowledge_boxes_[player_id]; }

  knowledge_box& entity(id_t entity_id) { return entities_knowledge_boxes_[entity_id]; }

 private:
  knowledge_box global_knowledge_box_;
  std::unordered_map<id_t, knowledge_box> players_knowledge_boxes_;
  std::unordered_map<id_t, knowledge_box> entities_knowledge_boxes_;
};

inline id_t active_player_id(ai_knowledge& knowledge) {
  return knowledge.global().get<id_t>("active_player_id");
}

inline id_t active_entity_id(ai_knowledge& knowledge) {
  return knowledge.global().get<id_t>("active_entity_id");
}

}  // namespace ai
