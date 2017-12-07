#ifndef SIGNALS_H
#define SIGNALS_H

#include <functional>
#include <memory>
#include <vector>

//template <typename... Args>
class signal
{
public:
	using holder = std::shared_ptr<void>;
	using callback = std::function<void(holder)>;
	using weak_receiver = std::weak_ptr<callback>;
	using strong_receiver = std::shared_ptr<callback>;
	using receiver_vector = std::vector<weak_receiver>;

	strong_receiver add_receiver(const strong_receiver& rec)
	{
		receivers_.push_back(rec);
		return rec;
	}

	void send_event()
	{
		for (auto& receiver : receivers_)
		{
			if (!receiver.expired()) {
				auto ptr = receiver.lock();
				(*ptr)(ptr);
			}
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