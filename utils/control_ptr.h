//
// Created by abrdej on 30.01.18.
//

#ifndef PIGEONWAR_CONTROL_PTR_H
#define PIGEONWAR_CONTROL_PTR_H

#include <memory>

template <typename Tp>
class control_ptr
{
	std::shared_ptr<std::unique_ptr<Tp>> mem;
public:
	control_ptr() = default;
	explicit control_ptr(Tp* p)
			: mem(std::make_shared<std::unique_ptr<Tp>>(p)) {

	}
	control_ptr(const control_ptr&) = default;
	control_ptr& operator=(const control_ptr&) = default;
	control_ptr(control_ptr&&) = default;
	control_ptr& operator=(control_ptr&&) = default;

	void destroy() {
		*mem = nullptr;
	}
	bool exist() const {
		return *mem != nullptr;
	}
	Tp* operator->() const noexcept
	{
		return (*mem).get();
	}
};

#endif //PIGEONWAR_CONTROL_PTR_H
