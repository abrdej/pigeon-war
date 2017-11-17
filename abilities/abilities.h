#ifndef ABILITIES_H
#define ABILITIES_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <cassert>
#include <iostream>

class ability;

class abilities final
{
public:
	enum class ability_types { moving = 0, offensive, special, defensive, passive };

	void add_ability(ability_types type, const std::shared_ptr<ability>& ability_ptr)
	{
        abilities_[static_cast<int>(type)] = ability_ptr;
	}
	std::shared_ptr<ability> at(size_t index) const
	{
        auto it = abilities_.find(index);
        return it != std::end(abilities_) ? it->second : nullptr;
	}
	std::shared_ptr<ability> type(ability_types type) const
	{
        int index = static_cast<int>(type);
        return at(index);
	}
	size_t size() const
	{
		return abilities_.size();
	}
private:
	std::unordered_map<int, std::shared_ptr<ability>> abilities_;
};

#endif