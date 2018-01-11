#include "entity_drawer.h"
#include "view_constants.h"
#include "board_panel.h"
#include "common/health_field.h"

entity_drawer::entity_drawer(std::size_t entity_id, const bitmap_key& bmt_key)
    : entity_id(entity_id), bmt_key(bmt_key) {

    font.loadFromFile(resources_directory + "verdanab.ttf");
    sprite.setTexture(view::bitmap_center::get_bitmap(bmt_key));
}

void entity_drawer::change_bitmap(const bitmap_key& key) {
    sprite.setTexture(view::bitmap_center::get_bitmap(key));
    bmt_key = key;
}

bitmap_key entity_drawer::get_bitmap_key() {
    return bmt_key;
}

void entity_drawer::render_text(int entity_health, sf::Vector2f position, std::size_t entity_id, sf::RenderWindow& window)
{
    if (entity_health == indestructible)
        return;

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(entity_health));
    text.setCharacterSize(18);

//    if (players::player_for_entity(entity_id) == "tester1") {
//        text.setColor(sf::Color(0, 51, 102));
//    } else if (players::player_for_entity(entity_id) == "tester2") {
//        text.setColor(sf::Color(102, 0, 0));
//    } else {
        text.setColor(sf::Color(32, 32, 32));
//    }

    text.setPosition(position);

    //sf::FloatRect backgroundRect = text.getLocalBounds();
    //sf::CircleShape background(backgroundRect.width);
    //background.setFillColor(sf::Color::Red);

    //window.draw(background, text.getTransform());
    window.draw(text);

}

void entity_drawer::draw(sf::RenderWindow& window, size_t col, size_t row, int health) {

    auto position = sf::Vector2f(view::board_indexies_to_point(col, row));
    sprite.setPosition(position);

    health_pos = position;
    health_pos.x += view::constants::field_size / 4.f;
    health_pos.y -= view::constants::field_size / 4.f;

    window.draw(sprite);
    render_text(health, health_pos, entity_id, window);
}