//
// Created by abrdej on 18.11.17.
//

#ifndef PIGEONWAR_ENTITY_DRAWER_H
#define PIGEONWAR_ENTITY_DRAWER_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <core/board.h>
#include <set>
#include "bitmap_center.h"
#include "drawable.h"
#include "board_panel.h"
#include "view_constants.h"
#include "core/players.h"

struct entity_drawer : drawable {

    std::size_t entity_id;
    bitmap_key bmt_key;
    sf::Sprite sprite;
    int health{0};
    sf::Vector2f health_pos;
    sf::Font font;

    explicit entity_drawer(std::size_t entity_id, const bitmap_key& bmt_key);

    void change_bitmap(const bitmap_key& key);
    bitmap_key get_bitmap_key() override;
    void render_text(int entity_health, sf::Vector2f position, std::size_t entity_id, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) override;
};

#endif //PIGEONWAR_ENTITY_DRAWER_H
