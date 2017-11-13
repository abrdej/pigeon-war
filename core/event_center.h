#ifndef EVENT_CENTER
#define EVENT_CENTER

#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <algorithm>

/*
template <typename EVENT, typename... Args>
class event_center
{
public:
	using func = std::function<void(Args...)>;
	using weak_receiver = std::weak_ptr<func>;
	using strong_receiver = std::shared_ptr<func>;
	using receiver_vector = std::vector<weak_receiver>;

	static strong_receiver add_receiver(const strong_receiver& rec)
	{
		if (this_center_ == nullptr)
			this_center_ = std::make_unique<event_center<EVENT, Args...>>();

		this_center_->receivers_.push_back(rec);
		return rec;
	}

	static void send_event(Args... args)
	{
		if (this_center_ == nullptr)
			this_center_ = std::make_unique<event_center<EVENT, Args...>>();

		for (auto& receiver : this_center_->receivers_)
		{
			if (!receiver.expired())
				(*receiver.lock())(args...);
		}
		this_center_->receivers_.erase(std::remove_if(std::begin(this_center_->receivers_),
			std::end(this_center_->receivers_), [](const weak_receiver& receiver)
		{
			return receiver.expired();
		}), std::end(this_center_->receivers_));
			
	}

private:
	receiver_vector receivers_;

	static std::unique_ptr<event_center<EVENT, Args...>> this_center_;
};

template <typename EVENT, typename... Args>
std::unique_ptr<event_center<EVENT, Args...>> event_center<EVENT, Args...>::this_center_ = nullptr;

namespace events
{
	struct event_end_turn
	{
	};
}
*/

#endif