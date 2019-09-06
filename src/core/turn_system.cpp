#include <core/turn_system.h>

void turn_system::end_turn() {
  ++this_turn_;
  next_turn_signal_();

  auto result = on_turn_scheduled_.equal_range(this_turn_);
  for (auto it = result.first; it != result.second; ++it) {
    it->second();
  }
}

void turn_system::on_turn(std::uint32_t n, const turn_callback& callback) {
  on_turn_scheduled_.emplace(n, callback);
}
