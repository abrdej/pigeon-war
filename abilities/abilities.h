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

//	template <typename AbilityType, typename... Args>
//	auto add(Args&&... args) {
//		auto ability = std::make_shared<AbilityType, Args...>(std::forward<Args>(args)...);
//		auto type = AbilityType::type;
//		int type_integer = static_cast<int>(type);
//		holder[type_integer] = ability;
//
//		enable(*ability);
//
////        if (std::is_member_function_pointer<decltype(&AbilityType::callback)>::value) {
////            callbacks[type_integer] = [&keep = *ability]() {
////                return keep.callback();
////            };
////        } else {
////            callbacks[type_integer];
////        }
//		bitmaps.emplace(type_integer, [&keep = *ability](){
//			return keep.get_bitmap_key();
//		});
//
//        return ability;
//	}
//    bool has_ability(size_t index) const {
//        return holder.find(index) != holder.end();
//    }
//    std::function<void()> get_callback(size_t index) const {
//        return callbacks.at(index);
//    }
//    std::string get_bitmap_key(size_t index) const {
//		return bitmaps.at(index)();
//    }

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
//	std::unordered_map<int, std::shared_ptr<void>> holder;
//	std::unordered_map<int, std::function<void()>> callbacks;
//	std::unordered_map<int, std::function<std::string()>> bitmaps;
//	std::unordered_map<int, std::string> hint;
};

#endif