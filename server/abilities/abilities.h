#ifndef ABILITIES_H
#define ABILITIES_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <SFML/Config.hpp>

class ability;

class abilities final
{
public:
	enum class ability_types { moving = 0, offensive, special, defensive, passive };

	bool is_active{true};

	void add_ability(ability_types type, const std::shared_ptr<ability>& ability_ptr)
	{
        abilities_[static_cast<std::int32_t>(type)] = ability_ptr;
	}
	std::shared_ptr<ability> at(std::int32_t index) const
	{
        auto it = abilities_.find(index);
        return it != std::end(abilities_) ? it->second : nullptr;
	}
	std::shared_ptr<ability> type(ability_types type) const
	{
		std::int32_t index = static_cast<std::int32_t>(type);
        return at(index);
	}
	auto size() const
	{
		return abilities_.size();
	}
private:
	std::unordered_map<std::int32_t, std::shared_ptr<ability>> abilities_;

//	std::unordered_map<std::int32_t, std::shared_ptr<void>> holder;
//	std::unordered_map<std::int32_t, std::function<void()>> callbacks;
//	std::unordered_map<std::int32_t, std::function<std::string()>> bitmaps;
//	std::unordered_map<std::int32_t, std::string> hint;
};

#endif