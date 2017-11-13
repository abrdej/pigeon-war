#ifndef DRAIN_H
#define DRAIN_H

#include <core/turn.h>
#include "abilities/ability.h"

class drain final : public ability, turn_events_helper::every_turn_callback_helper
{
public:
	drain();
	
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t index_from, size_t index_on);

private:
	static const size_t range_ = 1;
	static const size_t damage_ = 10;
	static const size_t drain_ = 4;
	bool used{false};
};

#endif