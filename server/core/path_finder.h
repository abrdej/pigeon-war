#ifndef PATH_FINDER_H
#define PATH_FINDER_H

#include "utils/graph.h"
#include <map>
#include <functional>

class path_finder
{
public:
	explicit path_finder(bool all_fields = false);
	void calc(sf::Uint64 from_index);

	sf::Uint64 find_first_satisfy_conditions(sf::Uint64 from_index,
										 const std::function<bool(sf::Uint64)>& condition_fn);

	void get_possible_movements(std::vector<sf::Uint64>& movements,
								std::vector<sf::Uint64>& costs,
								sf::Int32 range);

	sf::Uint64 distance_to(sf::Uint64 index);
	void path_to(sf::Uint64 index, std::vector<sf::Uint64>& path);

private:
	graph<sf::Int32, sf::Int32> graph_;
	std::map<sf::Int32, sf::Int32> distance_map_;
	std::map<sf::Int32, sf::Int32> sequence_map_;
	sf::Uint64 start_index_;
};

namespace board_helper
{
void calc_straight(sf::Uint64 from_index,
				   std::vector<sf::Uint64>& movements,
				   std::vector<sf::Uint64>& costs,
				   sf::Int32 range,
				   bool skip_obstacles = false);

void neighboring_fields(sf::Uint64 for_index, std::vector<sf::Uint64>& fields, bool available);

void circle(sf::Uint64 for_index, std::vector<sf::Uint64>& fields, bool available);

void all_free(std::vector<sf::Uint64>& fields);
};

#endif