#include "board.h"

std::array<std::vector<std::uint32_t>, board::cols_n * board::rows_n> board::fields_;

std::function<void()> board::observer;