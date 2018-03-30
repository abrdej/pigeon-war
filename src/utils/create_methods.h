#ifndef CREATE_METHODS_H
#define CREATE_METHODS_H

#include <memory>

#include "entities/shooter.h"

namespace create_methods
{
	template <typename T>
	std::shared_ptr<T> make()
	{
		return std::make_shared<T>();
	}
}


#endif