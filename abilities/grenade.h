#ifndef GRENADE_H
#define GRENADE_H

#include "abilities/ability.h"
#include <vector>

class grenade final : public ability
{
public:
	grenade();

private:
	void prepare(size_t for_index) override;
	void use(size_t index_on);
	void play_animation(size_t from_index, size_t to_index, const std::vector<size_t>& neightbords);

private:
	static const size_t range_ = 3;
	static const size_t damage_ = 12;
	bool used_;
};

#endif