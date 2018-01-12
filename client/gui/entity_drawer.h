//
// Created by abrdej on 18.11.17.
//

#ifndef PIGEONWAR_ENTITY_DRAWER_H
#define PIGEONWAR_ENTITY_DRAWER_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "drawable.h"
#include "bitmap_center.h"

struct entity_drawer : drawable {

    sf::Uint64 entity_id;
    bitmap_key bmt_key;
    sf::Sprite sprite;
    sf::Vector2f health_pos;
    sf::Font font;

    explicit entity_drawer(sf::Uint64 entity_id, const bitmap_key& bmt_key);

    void change_bitmap(const bitmap_key& key);
    bitmap_key get_bitmap_key() override;
    void render_text(sf::Int32 entity_health, sf::Vector2f position, sf::Uint64 entity_id, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, sf::Uint64 col, sf::Uint64 row, sf::Int32 health) override;
};

#endif //PIGEONWAR_ENTITY_DRAWER_H
