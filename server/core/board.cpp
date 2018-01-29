#include "board.h"

std::array<std::vector<std::uint32_t>, board::cols_n * board::rows_n> board::fields_;

board::board_change_signal_type board::board_change_signal;