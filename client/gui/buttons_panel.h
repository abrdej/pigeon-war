#ifndef BUTTONS_PANEL_H
#define BUTTONS_PANEL_H

#include "my_button.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <common/bitmaps.h>

class entity;
class entity_manager;

namespace view
{
class buttons_panel final
{
public:
    void prepare();
    void draw(sf::RenderWindow& window);
    bool is_hit(sf::Vector2i cursor) const;
    size_t hit_button(sf::Vector2i cursor) const;
    void set_for_entity_for(const std::string& entity_name,
							const std::array<bitmap_key, 6>& button_bitmaps);

    void set_hint_for(const sf::Vector2f& pos, std::size_t hint_idx);
    void remove_hint();

    void draw_hint(sf::RenderWindow& window);

private:
    std::vector<my_button> buttons_;
    std::vector<sf::Sprite> sprites_;
    static sf::Texture end_turn_bitmap_;

    sf::Font name_font;
    std::string entity_name;
    sf::Sprite entity_logo;

    std::array<std::string, 5> hints;
    static const std::size_t no_hint = std::numeric_limits<std::size_t>::max();
    std::size_t hint_button_idx{no_hint};
    sf::Vector2f hint_pos;
};

}

#endif