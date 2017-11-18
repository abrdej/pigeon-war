#ifndef TONGUE_OF_FIRE_H
#define TONGUE_OF_FIRE_H

#include "abilities/ability.h"
#include "core/turn.h"

class tongue_of_fire final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	tongue_of_fire();
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_bullet_animation(size_t from_index, size_t to_index);
	void refresh_usable();
private:
	static const size_t range_ = 7;
	static const size_t damage_ = 9;
	bool used_;
};

#endif