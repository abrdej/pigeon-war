#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "abilities/ability.h"
#include "possible_movement.h"
#include "core/turn.h"
#include <functional>

class moveable final : public ability, turn_events_helper::every_turn_callback_helper {
public:
    enum class types {
        path,
        straight
    };
	explicit moveable(size_t range, types type = types::path)
		: range_(range),
		  actual_range_(range),
          type(type)
	{
		onEveryRound([this]() {
			refresh_range();
		});
	}
private:
	void prepare(size_t for_index) override;
	size_t range() const { return actual_range_; }
	void use_move(size_t n)
	{
		if (n > actual_range_)
			throw std::out_of_range("move is out of entity range");
		actual_range_ -= n;
	}
	void refresh_range() { actual_range_ = range_; }

	void move(size_t index_to);

private:
	size_t range_;
	size_t actual_range_;
    types type;
};



#endif