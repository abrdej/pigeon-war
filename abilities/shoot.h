#ifndef SHOOT_H
#define SHOOT_H

#include "abilities/ability.h"
#include "core/turn.h"

class shoot final : public ability, protected turn_events_helper::every_turn_callback_helper
{
public:
	shoot();
private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_bullet_animation(std::size_t entity_id, size_t from_index, size_t to_index);
	void refresh_usable();

private:
	static const size_t range_ = 3;
	static const size_t damage_ = 6;
	static const size_t bullets_n = 2;
	size_t bullets_;
};

#endif