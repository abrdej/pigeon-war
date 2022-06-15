#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <boost/range/algorithm/find_if.hpp>

#include <abilities/ability.h>

class abilities final {
public:
    bool is_active{true};

    void add_ability(std::shared_ptr<ability> ability_ptr) {
        abilities_.emplace_back(ability_ptr, typeid(*ability_ptr));
    }

    std::shared_ptr<ability> of_type(const ability_types& type) const {
        auto it = boost::range::find_if(abilities_,
                                        [type](const std::pair<std::shared_ptr<ability>, std::type_index>& x) -> bool {
                                            return x.first->type() == type;
                                        });
        return it != std::end(abilities_) ? it->first : nullptr;
    }

    template <typename Type>
    std::shared_ptr<Type> get() const {
        auto it = boost::range::find_if(abilities_,
                                        [](const std::pair<std::shared_ptr<ability>, std::type_index>& x) -> bool {
                                            return x.second == std::type_index(typeid(Type));
                                        });
        return it != std::end(abilities_) ? std::static_pointer_cast<Type>(it->first) : nullptr;
    }

    std::shared_ptr<ability> at(std::uint32_t index) const {
        return index < abilities_.size() ? abilities_[index].first : nullptr;
    }

    auto size() const {
        return abilities_.size();
    }

private:
    std::vector<std::pair<std::shared_ptr<ability>, std::type_index>> abilities_;
};
