#pragma once

#include <limits>
#include <list>
#include <queue>
#include <unordered_map>
#include <vector>

struct graph {
  using vertex_descriptor = std::uint32_t;
  using vertex_type = std::vector<vertex_descriptor>;
  using adjacency_list_type = std::vector<vertex_type>;

  void set_size(std::size_t n) { vertices.resize(n); }
  [[nodiscard]] auto size() const { return vertices.size(); }

  void add_edge(const vertex_descriptor& from, const vertex_descriptor& to) {
    vertices[from].emplace_back(to);
  }

  adjacency_list_type vertices;
};

template <typename T>
void breadth_search(graph& g,
                    const typename graph::vertex_descriptor& initial_vertex,
                    std::vector<T>& distances_map,
                    std::vector<typename graph::vertex_descriptor>& sequence_map) {
  using vertex_descriptor = typename graph::vertex_descriptor;

  distances_map = std::vector<T>(g.size(), std::numeric_limits<T>::max());
  sequence_map = std::vector<vertex_descriptor>(g.size());

  auto& vertices = g.vertices;

  std::queue<vertex_descriptor> q;
  q.push(initial_vertex);

  distances_map[initial_vertex] = T();
  sequence_map[initial_vertex] = vertex_descriptor();

  while (!q.empty()) {
    auto vertex = q.front();
    auto& adjacent_vertices = vertices[vertex];
    q.pop();

    for (auto&& adjacent_vertex : adjacent_vertices) {
      if (distances_map[adjacent_vertex] == std::numeric_limits<std::int32_t>::max()) {
        distances_map[adjacent_vertex] = distances_map[vertex] + 1;
        sequence_map[adjacent_vertex] = vertex;
        q.push(adjacent_vertex);
      }
    }
  }
}

template <typename T, typename Condition>
auto breadth_search(graph& g,
                    const typename graph::vertex_descriptor& initial_vertex,
                    std::vector<T>& distances_map,
                    std::vector<typename graph::vertex_descriptor>& sequence_map,
                    Condition condition) {
  using vertex_descriptor = typename graph::vertex_descriptor;

  distances_map = std::vector<T>(g.size(), std::numeric_limits<T>::max());
  sequence_map = std::vector<vertex_descriptor>(g.size());

  auto& vertices = g.vertices;

  std::queue<vertex_descriptor> q;
  q.push(initial_vertex);

  distances_map[initial_vertex] = T();
  sequence_map[initial_vertex] = vertex_descriptor();

  while (!q.empty()) {
    auto vertex = q.front();
    auto& adjacent_vertices = vertices[vertex];
    q.pop();

    if (condition(vertex)) return vertex;

    for (auto adjacent_vertex : adjacent_vertices) {
      if (distances_map[adjacent_vertex] == std::numeric_limits<std::int32_t>::max()) {
        distances_map[adjacent_vertex] = distances_map[vertex] + 1;
        sequence_map[adjacent_vertex] = vertex;
        q.push(adjacent_vertex);
      }
    }
  }

  return std::numeric_limits<vertex_descriptor>::max();
}
