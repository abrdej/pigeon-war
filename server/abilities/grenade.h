#ifndef GRENADE_H
#define GRENADE_H

#include "ability.h"
#include <vector>

class grenade final : public ability
{
public:
	grenade() = default;

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::grenade;
	}

private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index, const std::vector<size_t>& neightbords);

private:
	const int range = 3;
	const int damage = 12;
	bool used_{false};
};

#endif