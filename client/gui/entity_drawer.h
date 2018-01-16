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

    std::uint32_t entity_id;
    bitmap_key bmt_key;
    sf::Sprite sprite;
    sf::Vector2f health_pos;
    sf::Font font;

    explicit entity_drawer(std::uint32_t entity_id, const bitmap_key& bmt_key);

    void change_bitmap(const bitmap_key& key);
    bitmap_key get_bitmap_key() override;
    void render_text(std::int32_t entity_health, sf::Vector2f position, std::uint32_t entity_id, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, std::uint32_t col, std::uint32_t row, std::int32_t health) override;
};

#endif //PIGEONWAR_ENTITY_DRAWER_H
