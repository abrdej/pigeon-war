//
// Created by abrdej on 18.11.17.
//

#ifndef PIGEONWAR_DRAWABLE_H
#define PIGEONWAR_DRAWABLE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

struct drawable {
    using ptr_type = std::shared_ptr<drawable>;
    virtual void draw(sf::RenderWindow& window) = 0;
};


#endif //PIGEONWAR_DRAWABLE_H
