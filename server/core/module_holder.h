#ifndef MODULE_HOLDER_H
#define MODULE_HOLDER_H

#include <memory>
#include <unordered_map>
#include <typeindex>

class molude_holder
{
protected:
	virtual ~molude_holder() {}

public:
	template <typename T>
	std::shared_ptr<T> add(const std::shared_ptr<T>& m)
	{
		auto result = modules_.insert(std::make_pair(std::type_index(typeid(T)), m));
		return (result.second) ? m : std::static_pointer_cast<T>(modules_.at(std::type_index(typeid(T))));
	}

	template <typename T>
	bool contain() const
	{
		return modules_.find(std::type_index(typeid(T))) != std::end(modules_);
	}

	template <typename T>
	std::shared_ptr<T> get() const
	{
		auto it = modules_.find(std::type_index(typeid(T)));
		if (it != std::end(modules_))
			return std::static_pointer_cast<T>(it->second);
		else
			return std::shared_ptr<T>();
	}

	template <typename T>
	void erase()
	{
		modules_.erase(std::type_index(typeid(T)));
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<void>> modules_;
};

#endif