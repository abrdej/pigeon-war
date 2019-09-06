#pragma once

#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>

class module_holder {
 public:
  template <typename T, typename... Args>
  std::shared_ptr<T> add(Args &&... args) {
    return std::static_pointer_cast<T>(
        modules
            .emplace(std::type_index(typeid(T)), std::make_shared<T>(std::forward<Args>(args)...))
            .first->second);
  }

  template <typename T>
  bool contain() const {
    return modules.find(std::type_index(typeid(T))) != std::end(modules);
  }

  template <typename T>
  std::shared_ptr<T> get() const {
    auto it = modules.find(std::type_index(typeid(T)));
    if (it != std::end(modules))
      return std::static_pointer_cast<T>(it->second);
    else {
      std::cout << "get component which doesn't exist: " << typeid(T).name() << "\n";
      return std::shared_ptr<T>();
    }
  }

  template <typename T>
  std::shared_ptr<T> get() {
    auto it = modules.find(std::type_index(typeid(T)));
    if (it != std::end(modules))
      return std::static_pointer_cast<T>(it->second);
    else {
      std::cout << "get component which doesn't exist\n" << typeid(T).name() << "\n";
      return std::shared_ptr<T>();
    }
  }

  template <typename T>
  void erase() {
    modules.erase(std::type_index(typeid(T)));
  }

 private:
  std::unordered_map<std::type_index, std::shared_ptr<void>> modules;
};
