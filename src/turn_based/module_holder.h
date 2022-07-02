#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include <logging/logger.h>

class module_holder {
 public:
  template <typename T, typename... Args>
  std::shared_ptr<T> add(Args&& ... args) {
    return std::static_pointer_cast<T>(modules_.emplace(std::type_index(typeid(T)),
                                                        std::make_shared<T>(std::forward<Args>(args)...)).first->second);
  }

  template <typename T>
  bool contain() const {
    return modules_.find(std::type_index(typeid(T))) != std::end(modules_);
  }

  template <typename T>
  std::shared_ptr<T> get() const {
    auto it = modules_.find(std::type_index(typeid(T)));
    if (it != std::end(modules_))
      return std::static_pointer_cast<T>(it->second);
    else {
      LOG(error) << "get component which doesn't exist: " << typeid(T).name();
      return std::shared_ptr<T>();
    }
  }

  template <typename T>
  std::shared_ptr<T> get() {
    auto it = modules_.find(std::type_index(typeid(T)));
    if (it != std::end(modules_))
      return std::static_pointer_cast<T>(it->second);
    else {
      LOG(error) << "get component which doesn't exist: " << typeid(T).name();
      return std::shared_ptr<T>();
    }
  }

  template <typename T>
  void erase() {
    modules_.erase(std::type_index(typeid(T)));
  }

 private:
  std::unordered_map<std::type_index, std::shared_ptr<void>> modules_;
};
