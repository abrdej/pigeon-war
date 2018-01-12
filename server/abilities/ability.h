#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
#include <common/bitmaps.h>

class ability
{
protected:
	virtual ~ability() = default;
public:
	void operator()(sf::Uint64 index)
	{
		prepare(index);
	}
	virtual std::string hint() const {
		return "hint";
	}
	virtual bitmap_key get_bitmap_key() const = 0;
private:
	virtual void prepare(sf::Uint64 for_index) = 0;
};

struct passive_ability : ability {
	void prepare(sf::Uint64 for_index) override {}
};

#endif