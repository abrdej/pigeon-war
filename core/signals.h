#ifndef SIGNALS_H
#define SIGNALS_H

#include <functional>
#include <memory>
#include <vector>

template <typename... Args>
class signal
{
public:
	using callback = std::function<void(Args...)>;
	using weak_receiver = std::weak_ptr<callback>;
	using strong_receiver = std::shared_ptr<callback>;
	using receiver_vector = std::vector<weak_receiver>;

	strong_receiver add_receiver(const strong_receiver& rec)
	{
		receivers_.push_back(rec);
		return rec;
	}

	void send_event(Args... args)
	{
		for (auto& receiver : receivers_)
		{
			if (!receiver.expired())
				(*receiver.lock())(args...);
		}
		receivers_.erase(std::remove_if(std::begin(receivers_),
			std::end(receivers_), [](const weak_receiver& receiver)
		{
			return receiver.expired();
		}), std::end(receivers_));

	}
private:
	receiver_vector receivers_;
};

#endif