#pragma once

#include <functional>
#include <memory>

template <typename... Args>
class hard_callback_holder;

template <typename... Args>
class callback_holder {
 public:
  callback_holder() = default;
  explicit callback_holder(std::function<void(Args...)> fn)
      : ptr_(std::make_shared<std::function<void(Args...)>>(fn)) {}
  callback_holder(const callback_holder&) = default;
  callback_holder& operator=(const callback_holder&) = default;
  callback_holder(callback_holder&&) noexcept = default;
  callback_holder& operator=(callback_holder&&) noexcept = default;

  void destroy() {
    if (ptr_) *ptr_ = nullptr;
  }
  [[nodiscard]] bool exist() const { return ptr_ && *ptr_ != nullptr; }
  void operator()(Args&& ... args) { return (*ptr_)(std::forward<Args>(args)...); }
  void operator()(Args&& ... args) const { return (*ptr_)(std::forward<Args>(args)...); }
  friend class hard_callback_holder<Args...>;

 private:
  std::shared_ptr<std::function<void(Args...)>> ptr_;
};

template <typename... Args>
class hard_callback_holder {
 public:
  explicit hard_callback_holder(callback_holder<Args...> holder) {
    holder_ = holder_deleter(holder.ptr_.get());
  }
  hard_callback_holder& operator=(callback_holder<Args...> holder) {
    holder_ = holder_deleter(holder.ptr_.get());
  }
  hard_callback_holder() = default;
  hard_callback_holder(const hard_callback_holder&) = delete;
  hard_callback_holder& operator=(const hard_callback_holder&) = delete;
  hard_callback_holder(hard_callback_holder&&) noexcept = default;
  hard_callback_holder& operator=(hard_callback_holder&&) noexcept = default;

 private:
  struct deleter {
    void operator()(std::function<void(Args...)>* p) {
      if (p) {
        (*p) = nullptr;
      }
    }
  };
  using holder_deleter = std::unique_ptr<std::function<void(Args...)>, deleter>;
  holder_deleter holder_{nullptr};
};
