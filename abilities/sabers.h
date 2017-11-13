#ifndef SABERS_H
#define SABERS_H

#include "abilities/ability.h"
#include <vector>
#include "core/turn.h"

class sabers final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	sabers();
private:
	void prepare(size_t for_index) override;
	void target(size_t on);
	void use(size_t index_on);
	void play_animation(size_t index_from, size_t index_on);

private:
	static const size_t range_ = 1;
	static const size_t damage_ = 7;
	std::vector<size_t> targets_;
	bool used{false};
};

#endif