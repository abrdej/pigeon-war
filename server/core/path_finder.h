#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "utils/graph.h"
#include <map>
#include <functional>

class path_finder
{
public:
	explicit path_finder(bool all_fields = false);
	void calc(std::uint32_t from_index);

	std::uint32_t find_first_satisfy_conditions(std::uint32_t from_index,
										 const std::function<bool(std::uint32_t)>& condition_fn);

	void get_possible_movements(std::vector<std::uint32_t>& movements,
								std::vector<std::uint32_t>& costs,
								std::int32_t range);

	std::uint32_t distance_to(std::uint32_t index);
	void path_to(std::uint32_t index, std::vector<std::uint32_t>& path);

private:
	graph<std::int32_t, std::int32_t> graph_;
	std::map<std::int32_t, std::int32_t> distance_map_;
	std::map<std::int32_t, std::int32_t> sequence_map_;
	std::uint32_t start_index_;
};

namespace board_helper
{
void calc_straight(std::uint32_t from_index,
				   std::vector<std::uint32_t>& movements,
				   std::vector<std::uint32_t>& costs,
				   std::int32_t range,
				   bool skip_obstacles = false);

void neighboring_fields(std::uint32_t for_index, std::vector<std::uint32_t>& fields, bool available);

void circle(std::uint32_t for_index, std::vector<std::uint32_t>& fields, bool available);

void all_free(std::vector<std::uint32_t>& fields);
};

#endif