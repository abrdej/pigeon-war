#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>

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
private:
	virtual void prepare(size_t for_index) = 0;
};

#endif