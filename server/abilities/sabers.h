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
	void prepare(sf::Uint64 for_index) override;
	void target(sf::Uint64 on);
	void use(sf::Uint64 index_on);

private:
	const sf::Int32 range = 1;
	const sf::Int32 damage = 7;
	std::vector<sf::Uint64> targets_;
};

#endif