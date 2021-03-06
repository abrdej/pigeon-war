#pragma once

#include <cstddef>
#include <memory>
#include <typeindex>
#include <unordered_map>

/**
 * @brief Container for all building blocks of game.
 */
class game {
  using any_ptr = std::shared_ptr<void>;
  static std::unordered_map<std::type_index, any_ptr> blocks;

 public:
  template <typename Block>
  static Block& get() {
    auto it = blocks.find(typeid(Block));
    if (it == std::end(blocks)) {
      it = blocks.emplace(typeid(Block), std::make_shared<Block>()).first;
    }
    return *std::static_pointer_cast<Block>(it->second);
  }
};

template <typename Block>
auto& game_get() {
  return game::get<Block>();
}
