#pragma once

#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

/**
 * @brief Container for all building blocks of game.
 */
class game {
 public:
  static game& get_game();

  template <typename Block>
  static Block& get() {
    auto& blocks = get_game().blocks_;
    auto it = blocks.find(typeid(Block));
    if (it == std::end(blocks)) {
      it = blocks.emplace(typeid(Block), std::make_shared<Block>()).first;
      // required to ensure destruction order of blocks.
      get_game().ordering_.push_back(it->second);
    }
    return *std::static_pointer_cast<Block>(it->second);
  }

 private:
  std::vector<std::shared_ptr<void>> ordering_;
  std::unordered_map<std::type_index, std::shared_ptr<void>> blocks_;
};

template <typename Block>
auto& game_get() {
  return game::get<Block>();
}
