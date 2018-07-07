//
// Created by abrdej on 06.02.18.
//

#ifndef PIGEONWAR_SKIRMISH_H
#define PIGEONWAR_SKIRMISH_H

#include <string>

class game;

std::string create_skirmish(game& game,
                            const std::string& map_name,
                            std::pair<std::uint32_t, std::uint32_t>& map_size);

#endif //PIGEONWAR_SKIRMISH_H
