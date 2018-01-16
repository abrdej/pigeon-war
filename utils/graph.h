#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <vector>
#include <map>
#include <list>
#include <limits>
#include <SFML/Config.hpp>

template <typename T, typename C>
class graph;

template <typename KeyType, typename CostType>
struct vertex
{

	typedef CostType cost_type;
	typedef KeyType key_type;
	typedef std::pair<key_type, cost_type> edge_t;


	std::vector<edge_t> adj_list_;

	template <typename T, typename C>
	friend class graph;

	friend void djist(graph<std::string, std::int32_t>& grph, const std::string& initial_node,
		std::map<std::string, std::int32_t>& distances_map,
		std::map<std::string, std::string>& sequence_map);

	template <typename KT, typename CT>
	friend void breadth_search(graph<KT, CT>& grph,
		const typename graph<KT, CT>::key_type& initial_node,
		std::map<KT, CT>& distances_map,
		std::map<KT, CT>& sequence_map);

	template <typename KT, typename CT, typename ConditionFunc>
	friend KT breadth_search(graph<KT, CT>& grph,
		const typename graph<KT, CT>::key_type& initial_node,
		std::map<KT, CT>& distances_map,
		std::map<KT, KT>& sequence_map,
		const ConditionFunc& condition_func);
};

template <typename KeyType, typename CostType>
struct graph
{
	typedef KeyType key_type;
	typedef CostType cost_type;
	typedef vertex<key_type, cost_type> vertex_type;
	typedef std::map<key_type, vertex_type> map_type;

	inline void add_vertex(const key_type& key);
	inline void add_egde(const key_type& from, const key_type& to, const cost_type& cost = cost_type());
	inline std::uint64_t size() const { return verticies_.size(); }

	map_type verticies_;

	friend void djist(graph<std::string, std::int32_t>& grph, const std::string& initial_node,
		std::map<std::string, std::int32_t>& distances_map,
		std::map<std::string, std::string>& sequence_map);

	template <typename KT, typename CT>
	friend void breadth_search(graph<KT, CT>& grph,
		const typename graph<KT, CT>::key_type& initial_node,
		std::map<KT, CT>& distances_map,
		std::map<KT, KT>& sequence_map);

	template <typename KT, typename CT, typename ConditionFunc>
	friend KT breadth_search(graph<KT, CT>& grph,
		const typename graph<KT, CT>::key_type& initial_node,
		std::map<KT, CT>& distances_map,
		std::map<KT, KT>& sequence_map,
		const ConditionFunc& condition_func);
};

template <typename Key, typename CostType>
inline void graph<Key, CostType>::add_vertex(const key_type& key)
{
	verticies_[key];
}

template <typename Key, typename CostType>
inline void graph<Key, CostType>::add_egde(const key_type& from, const key_type& to, const cost_type& cost)
{
	verticies_[to];
	verticies_[from].adj_list_.push_back(std::make_pair(to, cost));
}

typedef std::pair<std::string, std::int32_t> pair_type;

struct mypair_comp
{
	bool operator()(const pair_type& lhs, const pair_type& rhs)
	{
		return lhs.second < rhs.second;
	}
};

template <typename KeyType, typename ValueType1, typename ValueType2>
void fill_map(const std::map<KeyType, ValueType1>& source, std::map<KeyType, ValueType2>& destination, const ValueType2& value)
{
	for (auto it = std::begin(source); it != std::end(source); ++it)
		destination[it->first] = value;
}
/*
void djist(graph<std::string, std::int32_t>& grph, const std::string& initial_node,
	std::map<std::string, std::int32_t>& distances_map,
	std::map<std::string, std::string>& sequence_map)
{
	// get verticies
	auto& verticies = grph.verticies_;

	// get initial node
	auto& init_it = verticies.find(initial_node);
	if (init_it == std::end(verticies))
		return; // error

	auto& start_key = init_it->first;

	typedef std::pair<std::string, std::int32_t> path_t;
	path_t vrec;

	std::priority_queue<path_t, std::vector<path_t>, mypair_comp> pq;
	pq.push(std::make_pair(start_key, 0));

	// scwolfch map
	std::map<std::string, std::int32_t> scwolfch_map;
	fill_map(verticies, scwolfch_map, 0);

	// distance map
	fill_map(verticies, distances_map, std::numeric_limits<std::int32_t>::max());
	distances_map[start_key] = 0;

	// sequence map
	sequence_map[start_key] = "";

	for (std::uint64_t nodes_seen = 0; nodes_seen < verticies.size(); ++nodes_seen)
	{
		do
		{
			if (pq.empty())
				return;

			vrec = pq.top();
			pq.pop();

		} while (scwolfch_map[vrec.first] != 0);

		auto& v_key = vrec.first;
		auto& adj_list = verticies[v_key].adj_list_;
		scwolfch_map[v_key] = 1;

		for (std::uint64_t i = 0; i < adj_list.size(); ++i)
		{
			auto& edge = adj_list[i];
			auto& w_dest_key = edge.first;
			auto w_cost = edge.second;

			if (w_cost < 0)
				return; // error

			if (distances_map[w_dest_key] > distances_map[v_key] + w_cost)
			{
				distances_map[w_dest_key] = distances_map[v_key] + w_cost;
				sequence_map[w_dest_key] = v_key;
				pq.push(std::make_pair(w_dest_key, w_cost));
			}
		}
	}
}*/

template <typename KeyType, typename CostType>
void breadth_search(graph<KeyType, CostType>& grph,
	const typename graph<KeyType, CostType>::key_type& initial_node,
	std::map<KeyType, CostType>& distances_map,
	std::map<KeyType, KeyType>& sequence_map)
{
	distances_map.clear();
	sequence_map.clear();

	// get verticies
	auto& verticies = grph.verticies_;

	// get initial node
	auto init_it = verticies.find(initial_node);
	if (init_it == std::end(verticies))
		return; // error

	auto& start_key = init_it->first;
	std::list<KeyType> q;
	q.push_back(start_key);

	// fill distance map with INFINITY (maximum of CostType)
	fill_map(verticies, distances_map, std::numeric_limits<CostType>::max());

	distances_map[start_key] = KeyType();
	sequence_map[start_key] = KeyType();

	while (!q.empty())
	{
		auto v_key = q.front();
		auto& v = verticies[v_key];
		q.pop_front();

		for (std::uint64_t i = 0; i < v.adj_list_.size(); ++i)
		{
			auto& edge = v.adj_list_[i];
			auto& w_dest_key = edge.first;

			if (distances_map[w_dest_key] == std::numeric_limits<std::int32_t>::max())
			{
				distances_map[w_dest_key] = distances_map[v_key] + 1;
				sequence_map[w_dest_key] = v_key;
				q.push_back(w_dest_key);
			}
		}
	}
}

template <typename KeyType, typename CostType, typename ConditionFunc>
KeyType breadth_search(graph<KeyType, CostType>& grph,
	const typename graph<KeyType, CostType>::key_type& initial_node,
	std::map<KeyType, CostType>& distances_map,
	std::map<KeyType, KeyType>& sequence_map,
	const ConditionFunc& condition_func)
{
	distances_map.clear();
	sequence_map.clear();

	// get verticies
	auto& verticies = grph.verticies_;

	// get initial node
	auto init_it = verticies.find(initial_node);
	if (init_it == std::end(verticies))
	{
		throw std::exception();
		return KeyType{}; // error
	}
		

	auto& start_key = init_it->first;
	std::list<KeyType> q;
	q.push_back(start_key);

	// fill distance map with INFINITY (maximum of CostType)
	fill_map(verticies, distances_map, std::numeric_limits<CostType>::max());

	distances_map[start_key] = KeyType();
	sequence_map[start_key] = KeyType();

	while (!q.empty())
	{
		auto v_key = q.front();
		auto& v = verticies[v_key];
		q.pop_front();

		if (condition_func(v_key))
			return v_key;

		for (std::uint64_t i = 0; i < v.adj_list_.size(); ++i)
		{
			auto& edge = v.adj_list_[i];
			auto& w_dest_key = edge.first;

			if (distances_map[w_dest_key] == std::numeric_limits<std::int32_t>::max())
			{
				distances_map[w_dest_key] = distances_map[v_key] + 1;
				sequence_map[w_dest_key] = v_key;
				q.push_back(w_dest_key);
			}
		}
	}
	throw std::exception();
}

#endif