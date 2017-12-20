#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
#include <common/bitmaps.h>

class ability
{
protected:
	virtual ~ability() = default;
public:
	void operator()(size_t index)
	{
		prepare(index);
	}
	virtual std::string hint() const {
		return "hint";
	}
	virtual bitmap_key get_bitmap_key() const = 0;
private:
	virtual void prepare(size_t for_index) = 0;
};

#endif