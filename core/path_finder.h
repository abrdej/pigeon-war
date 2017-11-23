#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "utils/graph.h"
#include <map>
#include <functional>

class moveable;

class path_finder
{
public:
	explicit path_finder(bool all_fields = false);
	void calc(size_t from_index);

	size_t find_first_satisfy_conditions(size_t from_index,
										 const std::function<bool(size_t)>& condition_fn);

	void get_possible_movements(std::vector<size_t>& movements,
								std::vector<size_t>& costs,
								int range);

	size_t distance_to(size_t index);
	void path_to(size_t index, std::vector<size_t>& path);

private:
	graph<int, int> graph_;
	std::map<int, int> distance_map_;
	std::map<int, int> sequence_map_;
	size_t start_index_;
};

namespace board_helper
{
void calc_straight(size_t from_index,
				   std::vector<size_t>& movements,
				   std::vector<size_t>& costs,
				   int range,
				   bool skip_obstacles = false);

void neighboring_fields(size_t for_index, std::vector<size_t>& fields, bool available);

void all_free(std::vector<size_t>& fields);
};

#endif