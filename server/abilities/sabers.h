#ifndef SABERS_H
#define SABERS_H

#include "ability.h"
#include <vector>
#include "per_turn_usable.h"

class sabers final : public active_ability, per_turn_usable
{
public:

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::sabers;
	}

	std::string hint() const override;

private:
	void prepare(std::uint32_t for_index) override;
	void target(std::uint32_t on);
	void use(std::uint32_t index_on);

private:
	const std::int32_t range = 1;
	const std::int32_t damage = 7;
	std::vector<std::uint32_t> targets_;
};

#endif