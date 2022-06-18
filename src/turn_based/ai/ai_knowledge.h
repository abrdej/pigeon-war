#pragma once

#include <string>
#include <unordered_map>

#include <boost/any.hpp>

#include <turn_based/board.h>

namespace ai {

struct knowledge_box {
  std::unordered_map<std::string, boost::any> data_;
  template <typename T>
  T get(const std::string& key) {
    return boost::any_cast<T>(data_.at(key));
  }
  bool has(const std::string& key) const { return data_.count(key) != 0; }
  template <typename T>
  void insert(const std::string& key, const T& x) {
    data_[key] = x;
  }
};

struct ai_knowledge {
  knowledge_box global_knowledge_box_;
  std::unordered_map<std::uint32_t, knowledge_box> players_knowledge_boxes_;
  std::unordered_map<std::uint32_t, knowledge_box> entities_knowledge_boxes_;

  knowledge_box& global() { return global_knowledge_box_; }

  knowledge_box& player(std::uint32_t player_id) { return players_knowledge_boxes_[player_id]; }

  knowledge_box& entity(std::uint32_t entity_id) { return entities_knowledge_boxes_[entity_id]; }
};

inline std::uint32_t active_player_id(ai_knowledge& knowledge) {
  return knowledge.global().get<std::uint32_t>("active_player_id");
}

inline std::uint32_t active_entity_id(ai_knowledge& knowledge) {
  return knowledge.global().get<std::uint32_t>("active_entity_id");
}

inline std::uint32_t active_entity_index(ai_knowledge& knowledge) {
  return game_board().index_for(active_entity_id(knowledge));
}

}  // namespace ai
