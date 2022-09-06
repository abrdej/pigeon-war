#include <turn_based/utils/graph.h>

#include <gtest/gtest.h>

TEST(Grapth, BreadthSearch) {
  graph test_graph;

  test_graph.set_size(16);

  test_graph.add_edge(0, 1);
  test_graph.add_edge(1, 2);
  test_graph.add_edge(2, 6);
  test_graph.add_edge(6, 7);
  test_graph.add_edge(7, 11);
  test_graph.add_edge(9, 13);
  test_graph.add_edge(12, 13);
  test_graph.add_edge(8, 9);
  test_graph.add_edge(8, 9);

  std::vector<int> distances_map;
  std::vector<graph::vertex_descriptor> sequence_map;
  breadth_search(test_graph, 0, distances_map, sequence_map);

  ASSERT_EQ(distances_map.size(), test_graph.size());
  ASSERT_EQ(sequence_map.size(), test_graph.size());

  ASSERT_EQ(distances_map[1], 1);
  ASSERT_EQ(distances_map[2], 2);
  ASSERT_EQ(distances_map[3], std::numeric_limits<std::int32_t>::max());
  ASSERT_EQ(distances_map[6], 3);
  ASSERT_EQ(distances_map[7], 4);
  ASSERT_EQ(distances_map[11], 5);

  ASSERT_EQ(distances_map[12], std::numeric_limits<std::int32_t>::max());

  ASSERT_EQ(sequence_map[1], 0);
  ASSERT_EQ(sequence_map[7], 6);
  ASSERT_EQ(sequence_map[11], 7);
}
