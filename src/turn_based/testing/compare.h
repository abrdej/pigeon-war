#include <vector>

#include <turn_based/defs.h>

namespace testing {

void CompareWithoutOrdering(const std::vector<index_t>& current_indices,
                            const std::vector<index_t::value_type>& expected_indices);

}  // namespace testing
