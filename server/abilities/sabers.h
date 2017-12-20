#ifndef SABERS_H
#define SABERS_H

#include "ability.h"
#include <vector>
#include "core/turn.h"

class sabers final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	sabers();

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::sabers;
	}

private:
	void prepare(size_t for_index) override;
	void target(size_t on);
	void use(size_t index_on);
	void play_animation(size_t index_from, size_t index_on);

private:
	const int range = 1;
	const int damage = 7;
	std::vector<size_t> targets_;
	bool used{false};
};

#endif