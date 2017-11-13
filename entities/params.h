#ifndef PARAMS_H
#define PARAMS_H

struct params
{
	params(int health)
		: health_(health)
	{
	}
	int health_;
};

#endif