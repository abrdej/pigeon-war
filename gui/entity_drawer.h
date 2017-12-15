//
// Created by abrdej on 18.11.17.
//

#ifndef PIGEONWAR_ENTITY_DRAWER_H
#define PIGEONWAR_ENTITY_DRAWER_H

#include <SFML/Graphics/Sprite.hpp>
#include <managers/health_manager.h>
#include <SFML/Graphics/Text.hpp>
#include <core/board.h>
#include "managers/directions_manager.h"
#include "managers/types_manager.h"
#include "bitmap_center.h"
#include "drawable.h"
#include "board_panel.h"
#include "view_constants.h"
#include "core/players.h"

struct entity_drawer : drawable {

    std::size_t entity_id;
    sf::Sprite sprite;
    int health{0};
    sf::Vector2f health_pos;
    sf::Font font;

    explicit entity_drawer(std::size_t entity_id) : entity_id(entity_id) {
        font.loadFromFile("verdanab.ttf");

        sprite.setTexture(view::bitmap_center::get_image_for_entity(types_manager::component_for(entity_id)));
    }

    void render_text(int entity_health, sf::Vector2f position, std::size_t entity_id, sf::RenderWindow& window)
    {
        if (entity_health == indestructible)
            return;

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(entity_health));
        text.setCharacterSize(18);

        if (players::player_for_entity(entity_id) == "tester1") {
            text.setColor(sf::Color(0, 51, 102));
        } else if (players::player_for_entity(entity_id) == "tester2") {
            text.setColor(sf::Color(102, 0, 0));
        } else {
            text.setColor(sf::Color(32, 32, 32));
        }

        text.setPosition(position);

        //sf::FloatRect backgroundRect = text.getLocalBounds();
        //sf::CircleShape background(backgroundRect.width);
        //background.setFillColor(sf::Color::Red);

        //window.draw(background, text.getTransform());
        window.draw(text);

    }

    void draw(sf::RenderWindow& window) override {

        auto index = board::index_for(entity_id);
        auto pos = board::to_pos(index);

        auto position = sf::Vector2f(view::board_indexies_to_point(pos.first, pos.second));
        sprite.setPosition(position);

        sprite.setTextureRect(directions_manager::component_for(entity_id)
										   == directions::left ? sf::IntRect(60, 0, -60, 60)
                                                               : sf::IntRect(0, 0, 60, 60));

        health = healths_manager::component_for(entity_id).health;
        health_pos = position;
        health_pos.x += view::constants::field_size / 4.f;
        health_pos.y -= view::constants::field_size / 4.f;

        window.draw(sprite);
        render_text(health, health_pos, entity_id, window);
    }
};

#endif //PIGEONWAR_ENTITY_DRAWER_H
