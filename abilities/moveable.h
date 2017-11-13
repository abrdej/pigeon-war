#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "abilities/ability.h"
#include "core/event_center.h"
#include <memory>
#include <functional>
#include "core/turn.h"

class moveable final : public ability,
	protected turn_events_helper::every_turn_callback_helper
{
public:
	moveable(size_t range)
		: range_(range),
		  actual_range_(range)
	{
		onEveryTurn([this](){
			refresh_range();
		});
	}
private:
	virtual void prepare(size_t for_index) override;
	bool moved() const { return actual_range_ == 0; }
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
};

#endif