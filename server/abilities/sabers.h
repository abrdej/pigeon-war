#ifndef SABERS_H
#define SABERS_H

#include "ability.h"
#include <vector>
#include "per_turn_usable.h"

class sabers final : public ability, per_turn_usable
{
public:

	bitmap_key get_bitmap_key() const override {
		return bitmap_key::sabers;
	}

	std::string hint() const override;

private:
	void prepare(size_t for_index) override;
	void target(size_t on);
	void use(size_t index_on);

private:
	const int range = 1;
	const int damage = 7;
	std::vector<size_t> targets_;
};

#endif