#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <boost/range/algorithm/find_if.hpp>

#include <turn_based/ability.h>

using ability_ptr = std::shared_ptr<ability>;

/**
 * @brief Container for abilities.
 */
class abilities final {
 public:
  bool is_active{true};

  template <typename T>
  void add_ability(const std::shared_ptr<T>& new_ability) {
    abilities_.emplace_back(new_ability, typeid(T));
  }

  [[nodiscard]] ability_ptr of_type(const ability_types& type) const {
    auto it = boost::range::find_if(abilities_,
                                    [type](const std::pair<ability_ptr, std::type_index>& x) -> bool {
                                      return x.first->type() == type;
                                    });
    return it != std::end(abilities_) ? it->first : nullptr;
  }

  template <typename Type>
  [[nodiscard]] std::shared_ptr<Type> get() const {
    auto it =
        boost::range::find_if(abilities_, [](const std::pair<ability_ptr, std::type_index>& x) -> bool {
          return x.second == std::type_index(typeid(Type));
        });
    return it != std::end(abilities_) ? std::static_pointer_cast<Type>(it->first) : nullptr;
  }

  [[nodiscard]] ability_ptr at(std::uint32_t index) const {
    return index < abilities_.size() ? abilities_[index].first : nullptr;
  }

  [[nodiscard]] auto size() const {
    return abilities_.size();
  }

 private:
  std::vector<std::pair<ability_ptr, std::type_index>> abilities_;
};
