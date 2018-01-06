#include "animations_queue.h"

std::vector<animation_pack> animations_queue::queue;

std::function<void()> animations_queue::pull_fn;