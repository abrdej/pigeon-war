//
// Created by abrde on 04.12.2017.
//

#ifndef PIGEONWAR_SHOOTER_DRAWING_H
#define PIGEONWAR_SHOOTER_DRAWING_H

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

struct shooter_drawer : drawable {

    std::size_t entity_id;
    sf::Sprite sprite;
    int health{0};
    sf::Vector2f health_pos;
    sf::Font font;

    enum class States {
        normal,
        shoot
    };
    States state{States::normal};

    std::vector<sf::Texture> textures;

    explicit shooter_drawer(std::size_t entity_id)
            : entity_id(entity_id) {

        font.loadFromFile("verdanab.ttf");
        //sprite.setTexture(view::bitmap_center::get_image_for_entity(types_manager::component_for(entity_id)));

        textures.push_back(view::bitmap_center::get_bitmap("shooter"));
        textures.push_back(view::bitmap_center::get_bitmap("shooter_shoot"));
    }

    void set_state(const States& x) {
        state = x;
    }

    void render_text(int entity_health, sf::Vector2f position, sf::RenderWindow& window)
    {
        if (entity_health == indestructible)
            return;

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(entity_health));
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::Black);
        text.setPosition(position);
        window.draw(text);
    }

    void draw(sf::RenderWindow& window) override {

        sprite.setTexture(textures[static_cast<int>(state)]);

        auto index = board::index_for(entity_id);
        auto pos = board::to_pos(index);

        auto position = sf::Vector2f(view::board_indexies_to_point(pos.first, pos.second));
        sprite.setPosition(position);
        sprite.setTextureRect(directions_manager::component_for(entity_id)
                              == entity_definition::directions::left ? sf::IntRect(60, 0, -60, 60)
                                                                     : sf::IntRect(0, 0, 60, 60));

        health = healths_manager::component_for(entity_id).health;
        health_pos = position;
        health_pos.x += view::constants::field_size / 4.f;
        health_pos.y -= view::constants::field_size / 4.f;

        window.draw(sprite);
        render_text(health, health_pos, window);
    }
};

#endif //PIGEONWAR_SHOOTER_DRAWING_H
