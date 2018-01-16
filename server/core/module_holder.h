#ifndef MODULE_HOLDER_H
#define MODULE_HOLDER_H

#include <memory>
#include <unordered_map>
#include <typeindex>

class module_holder
{
public:
	template <typename T, typename... Args>
	std::shared_ptr<T> add(Args&&... args)
	{
		auto& module = modules[std::type_index(typeid(T))];
		module = std::make_shared<T>(std::forward<Args>(args)...);
		return std::static_pointer_cast<T>(module);
	}

	template <typename T>
	bool contain() const
	{
		return modules.find(std::type_index(typeid(T))) != std::end(modules);
	}

	template <typename T>
	std::shared_ptr<T> get() const
	{
		auto it = modules.find(std::type_index(typeid(T)));
		if (it != std::end(modules))
			return std::static_pointer_cast<T>(it->second);
		else
			return std::shared_ptr<T>();
	}

	template <typename T>
	void erase()
	{
		modules.erase(std::type_index(typeid(T)));
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<void>> modules;
};

#endif