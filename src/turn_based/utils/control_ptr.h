#pragma once

#include <memory>

template <typename Tp>
class control_ptr {
 public:
  control_ptr() = default;
  explicit control_ptr(Tp* p) : ptr_(std::make_shared<std::unique_ptr<Tp>>(p)) {}
  control_ptr(const control_ptr&) = default;
  control_ptr& operator=(const control_ptr&) = default;
  control_ptr(control_ptr&&) noexcept = default;
  control_ptr& operator=(control_ptr&&) noexcept = default;

  void destroy() { *ptr_ = nullptr; }
  [[nodiscard]] bool exist() const { return *ptr_ != nullptr; }
  Tp* operator->() const noexcept { return (*ptr_).get(); }

 private:
  std::shared_ptr<std::unique_ptr<Tp>> ptr_;
};
