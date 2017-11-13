#ifndef BULLET_H
#define BULLET_H

#include <memory>

class bullet final : public std::enable_shared_from_this<bullet>
{
public:
	bullet(size_t from_index, size_t to_index, double velocity);
	void run();

	double col_factor_;
	double row_factor_;

private:
	size_t from_index_;
	size_t to_index_;
	
	const double velocity_;
};

#endif