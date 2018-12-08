#include <core/turn_system.h>

void turn_system::end_turn() {
    ++turn_n;

    next_turn_signal();

    auto result = tasks.equal_range(turn_n);
    auto it = result.first;
    for (; it != result.second; ++it) {
        it->second();
    }
}

void turn_system::on_turn(std::uint32_t turn_n, const std::function<void()>& task) {
    tasks.emplace(turn_n, task);
}
