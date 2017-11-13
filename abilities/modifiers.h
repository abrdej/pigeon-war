#ifndef MODIFIERS_H
#define MODIFIERS_H

#include <map>
#include <memory>

class modifier;

class modifiers final
{
public:
	enum class modifiers_types { buff, debuff };

	void add_modifier(modifiers_types type, const std::shared_ptr<modifier>& modifier_ptr)
	{
		modifiers_.insert(std::make_pair(type, modifier_ptr));
	}
	std::shared_ptr<modifier> at(size_t index) const
	{
		if (modifiers_.size() <= index)
			return nullptr;

		auto it = std::begin(modifiers_);
		std::advance(it, index);
		return it->second;
	}
	std::shared_ptr<modifier> type(modifiers_types type) const
	{
		auto it = modifiers_.find(type);
		return it != std::end(modifiers_) ? it->second : nullptr;
	}
	size_t size() const
	{
		return modifiers_.size();
	}
private:
	std::map<modifiers_types, std::shared_ptr<modifier>> modifiers_;
};

#endif