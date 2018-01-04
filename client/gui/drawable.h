//
// Created by abrdej on 18.11.17.
//

#ifndef PIGEONWAR_DRAWABLE_H
#define PIGEONWAR_DRAWABLE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include "common/bitmaps.h"

struct drawable {
    using ptr_type = std::shared_ptr<drawable>;
    virtual void draw(sf::RenderWindow& window, size_t col, size_t row, int health) = 0;
    virtual bitmap_key get_bitmap_key() = 0;
};


#endif //PIGEONWAR_DRAWABLE_H