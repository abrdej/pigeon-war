#include <turn_based/testing/compare.h>

#include <set>

#include <boost/range/combine.hpp>
#include <gtest/gtest.h>

namespace testing {

void CompareWithoutOrdering(const std::vector<index_t>& current_indices,
                            const std::vector<index_t::value_type>& expected_indices) {
  std::set<index_t::value_type> ordered_indices;
  for (const auto& index : current_indices) {
    ordered_indices.insert(index.cast());
  }

  for (const auto& entry : boost::range::combine(ordered_indices, expected_indices)) {
    EXPECT_EQ(boost::get<0>(entry), boost::get<1>(entry));
  }
}

}  // namespace testing
