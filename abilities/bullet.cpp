#include "bullet.h"
#include "core/board.h"
#include <thread>
#include <chrono>

bullet::bullet(size_t from_index, size_t to_index, double velocity)
	: from_index_(from_index),
	to_index_(to_index),
	velocity_(velocity)
{
}

void bullet::run()
{
	
}