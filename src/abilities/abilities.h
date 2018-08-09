#ifndef ABILITIES_H
#define ABILITIES_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <typeindex>
#include <algorithm>
#include "ability.h"

class abilities final
{
public:
	bool is_active{true};

	void add_ability(std::shared_ptr<ability> ability_ptr) {

        abilities_.emplace_back(ability_ptr, typeid(*ability_ptr));
	}
	std::shared_ptr<ability> of_type(const ability_types& t) const {

		auto it = std::find_if(std::begin(abilities_), std::end(abilities_),
							   [t](const std::pair<std::shared_ptr<ability>, std::type_index>& x) -> bool {
								   return x.first->type() == t;
							   });
		if (it != std::end(abilities_)) {
			return it->first;
		} else {
			return nullptr;
		}
	}
	template <typename Type>
	std::shared_ptr<Type> get() const {

        auto it = std::find_if(std::begin(abilities_), std::end(abilities_),
							   [](const std::pair<std::shared_ptr<ability>, std::type_index>& x) -> bool {
								   return x.second == std::type_index(typeid(Type));
							   });
		if (it != std::end(abilities_)) {
			return std::static_pointer_cast<Type>(it->first);
		} else {
			return nullptr;
		}
	}
	std::shared_ptr<ability> at(std::uint32_t index) const {
		if (index < abilities_.size()) {
			return abilities_[index].first;
		} else {
			return nullptr;
		}
	}
	auto size() const {

		return abilities_.size();
	}
private:
	std::vector<std::pair<std::shared_ptr<ability>, std::type_index>> abilities_;
};

#endif